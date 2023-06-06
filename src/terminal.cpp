#include "terminal.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

namespace terminal{
	char* functions[1] = {"exec_cmd"};
	char** plugin_export(unsigned short int *count){
		*count = 1;
		return functions;
	}
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
	    FILE *stream = popen((char*)arg->argValuePtr,"r");
		int size = *((int*)(arg->argNext->argValuePtr));
		char *buffer = new char[size+1];
		fread(buffer,sizeof(char),size,stream);
		cout<<buffer<<endl;
		return plugin_api::PluginError::Success;
	}
};
