#include "loader.h"
#include <string.h>

#ifdef __linux__
	#incude <dlfcn.h>
	#define POSTFIX_SIZE 3
	#define POSTFIX ".so"
#endif

BOOL load_plugin(char *plugin_name){
	g_plugins = (plugin**)realloc(g_plugins,(g_count + 1) * sizeof(plugin*));
	g_plugins[g_count] = (plugin*)calloc(1,sizeof(plugin));
	
	char *dllname = (char*)calloc(strlen(plugin_name)+POSTFIX_SIZE+1,sizeof(char));
	dllname = strcpy(dllname,POSTFIX);
	
	#ifdef __linux__
		dlllib lib = dlopen(dllname,RTLD_LAZY);
		export_function plugin_export = (export_function)dlsym(lib,"plugin_export");
		g_plugins[g_count]->lib = lib;
	#endif
	
	unsigned short int count = 0;
	function_info *info = plugin_export(&count);
	
	if(count == 0) return FALSE;
	
	g_plugins[g_count]->count = count;
	
	for(unsigned short int i = 0;i < count;i++){
		g_plugins[g_count]->functions[i].info.name = (char*)calloc(strlen(info[i].name) + 1,sizeof(char));
		g_plugins[g_count]->functions[i].info.name = strcpy(g_plugins[g_count]->functions[i].info.name,info[i].name);
		g_plugins[g_count]->functions[i].info.type = info[i].type;
		
		#ifdef __linux__
			g_plugins[g_count]->functions[i].addrres = (function)dlsym(lib,info[i].name);
		#endif
	}
	
	g_count++;
	
	free(dllname);
	
	return TRUE;
}

void unload_plugin(char *plugin_name){
	unsigned short int plugin_id;
	
	for(unsigned short int i = 0;i < g_count;i++){
		if(strcmp(plugin_name,g_plugins[i]->name) == 0){
			plugin_id = i;
			break;
		}
	}
	
	plugin *deleted_plugin = g_plugins[plugin_id];
	g_plugins[plugin_id] = g_plugins[g_count - 1];
	g_count--;
	
	for(unsigned short int i = 0;i < deleted_plugin.count;i++){
		free(deleted_plugin->function.info.name);
	}
	
	#ifdef __linux__
		dlclose(g_plugins[g_count]->lib);
	#endif
	
	free(deleted_plugin);
}