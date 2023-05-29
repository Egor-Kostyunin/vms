#include "plugin.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cstdarg>

#ifdef __linux__
	#include <dlfcn.h>
	#define POSTFIX_SIZE 3
	#define POSTFIX ".so"
#endif

namespace plugin_api{
	
	const char *pluginsPath = static_cast<char*>("./Plugins/");
	
	plugin **g_plugins;
	
	unsigned int g_count = 0;
	
	bool is_loaded(char* plugin_name){
		for(int i = 0;i < g_count;i++){
			if(std::strcmp(plugin_name,g_plugins[i]->pluginName) == 0) return true;
		}
		return false;
	}
	
	PluginError load(char *plugin_name){
		//Выделяем новый блок памяти под плагин
		g_plugins = (plugin**)std::realloc(g_plugins,(g_count + 1) * sizeof(plugin*));
		g_plugins[g_count] = (plugin*)std::calloc(1,sizeof(plugin));
		
		//Формирукм имя динамической библиотеки
		char *dllname = (char*)std::calloc(std::strlen(pluginsPath)+std::strlen(plugin_name)+POSTFIX_SIZE+1,sizeof(char));
		dllname = std::strcpy(dllname,pluginsPath);
		dllname = std::strcat(dllname,plugin_name);
		dllname = std::strcat(dllname,POSTFIX);
		
		//Загружаем библиотеку плагина
		#ifdef __linux__
			void *lib = dlopen(dllname,RTLD_LAZY);
			export_function plugin_export = (export_function)dlsym(lib,"plugin_export");
			g_plugins[g_count]->dllLibrary = lib;
		#endif
		
		//Экспортируем функции плагина
		unsigned short int count = 0;
		function_info *info = plugin_export(&count);
		
		if(count <= 0) return PluginError::InvalidFunctionCount;
		
		//Загружаем функции плагина
		for(unsigned short int i = 0;i < count;i++){
			g_plugins[g_count]->pluginFunctions[i].functionInfo.functionName = (char*)std::calloc(strlen(info[i].functionName) + 1,sizeof(char));
			g_plugins[g_count]->pluginFunctions[i].functionInfo.functionName = std::strcpy(g_plugins[g_count]->pluginFunctions[i].functionInfo.functionName,info[i].functionName);
			g_plugins[g_count]->pluginFunctions[i].functionInfo.functionType = info[i].functionType;
			
			#ifdef __linux__
				g_plugins[g_count]->pluginFunctions[i].functionAddress = (function_address)dlsym(lib,info[i].functionName);
			#endif
		}
		
		g_count++;
	
		std::free(dllname);
		return PluginError::Success;
	}
	
	PluginError exec(char *plugin_name,char *function_name,pfarg *ret,pfarg *arg){
		unsigned short int plugin_id = 0;
		unsigned short int function_id = 0;
		bool plugin_not_found = true;
		bool function_not_found = true;
		//Ищем плагин
		for(unsigned short int i = 0;i < g_count;i++){
			if(std::strcmp(plugin_name,g_plugins[i]->pluginName) == 0){
				plugin_id = i;
				plugin_not_found = false;
			}
		}
		
		if(plugin_not_found) return PluginError::PluginNotFound;
		
		//Ищем функцию
		for(unsigned short int i = 0;i < MAX_FUNCTION_COUNT;i++){
			if(g_plugins[plugin_id]->pluginFunctions[i].functionInfo.functionType == FunctionType::NotLoad){
				break;
			}
			
			if(std::strcmp(function_name,g_plugins[plugin_id]->pluginFunctions[i].functionInfo.functionName) == 0){
				function_id = i;
				function_not_found = false;
				break;
			}
		}
		
		if(function_not_found) return PluginError::FunctionNotExists;
		
		//Вызов найденной функции
		
		//Функция NotInOut типа
		if(g_plugins[plugin_id]->pluginFunctions[function_id].functionInfo.functionType == FunctionType::NotInOut){
			try{
				return g_plugins[plugin_id]->pluginFunctions[function_id].functionAddress(nullptr,nullptr);
			}
			catch(...){
				std::cout<<function_name<<" crash with exeption"<<std::endl;
				return PluginError::FunctionCrash; 				
			}
		}
		
		//Функция In типа
		if(g_plugins[plugin_id]->pluginFunctions[function_id].functionInfo.functionType == FunctionType::In){
			//Проверка наличия аргументов
			if(arg == nullptr) return PluginError::NullArg;
			try{
				return g_plugins[plugin_id]->pluginFunctions[function_id].functionAddress(nullptr,arg);
			}
			catch(...){
				std::cout<<function_name<<" crash with exeption"<<std::endl;
				return PluginError::FunctionCrash; 				
			}
		}
		
		//Функция Out типа
		if(g_plugins[plugin_id]->pluginFunctions[function_id].functionInfo.functionType == FunctionType::Out){
			//Проверка наличия переменной для возврата результата
			if(ret == nullptr) return PluginError::NullRet;
			try{
				return g_plugins[plugin_id]->pluginFunctions[function_id].functionAddress(ret,nullptr);
			}
			catch(...){
				std::cout<<function_name<<" crash with exeption"<<std::endl;
				return PluginError::FunctionCrash; 				
			}
		}
		
		//Функция InOut типа
		if(g_plugins[plugin_id]->pluginFunctions[function_id].functionInfo.functionType == FunctionType::InOut){
			//Проверка наличия аргументов
			if(arg == nullptr) return PluginError::NullArg;
			//Проверка наличия переменной для возврата результата
			if(ret == nullptr) return PluginError::NullRet;
			try{
				return g_plugins[plugin_id]->pluginFunctions[function_id].functionAddress(ret,arg);
			}
			catch(...){
				std::cout<<function_name<<" crash with exeption"<<std::endl;
				return PluginError::FunctionCrash; 				
			}
		}
		
		return PluginError::Success;
	}
	
	void unload(char *plugin_name){
		unsigned short int plugin_id;
		
		if(!is_loaded(plugin_name)) return;
			
		for(unsigned short int i = 0;i < g_count;i++){
			if(strcmp(plugin_name,g_plugins[i]->pluginName) == 0){
				plugin_id = i;
				break;
			}
		}
		
		plugin *deleted_plugin = g_plugins[plugin_id];
		g_plugins[plugin_id] = g_plugins[g_count - 1];
		g_count--;
		
		for(unsigned short int i = 0;i < deleted_plugin->functionCount;i++){
			free(deleted_plugin->pluginFunctions[i].functionInfo.functionName);
		}
		
		#ifdef __linux__
			dlclose(g_plugins[g_count]->dllLibrary);
		#endif
		
		free(deleted_plugin);
	}
	
	pfarg* alloc_ret(unsigned short int count){
		return reinterpret_cast<pfarg*>(std::calloc(count,sizeof(pfarg)));
	}
	
	pfarg* create_arg_tuple(unsigned short int count,...){
		pfarg *arg_ptr = reinterpret_cast<pfarg*>(std::calloc(count,sizeof(pfarg)));
		va_list arg_list;
		va_start(arg_list,count);
		for(unsigned short int i = 0;i < count;i++){
			arg_ptr[i] = va_arg(arg_list,plugin_api::pfarg);
		}
		va_end(arg_list);
		return arg_ptr;
	}
};