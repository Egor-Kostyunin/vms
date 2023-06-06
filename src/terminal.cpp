#include "terminal.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

namespace treminal{
	plugin_api::function_info functions[1] = {(plugin_api::function_info){"exec_cmd",plugin_api::FunctionType::In}};
	plugin_api::function_info* plugin_export(unsigned short int *count){
		*count = 1;
		return functions;
	}
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
	    	FILE *stream = popen(arg[0].strText,"rw");
		int size = arg[1].intNumber;
		char *buffer = new char[size];
		fread(buffer,sizeof(char),size,stream);
		cout<<buffer<<endl;
		return plugin_api::PluginError::Success;
	}
};
