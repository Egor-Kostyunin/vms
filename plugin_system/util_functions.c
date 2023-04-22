#include "loader.h"
#include <string.h>

unsigned short int get_plugin_id(char *plugin_name){
	for(unsigned short int i = 0;i < g_count;i++){
		if(strcmp(plugin_name,g_plugins[i]->name) == 0){
			return i;
		}
	}
	
	return 0;
}

void set_arg_tuple(pfarg *arg_tuple){
	g_arg_tuple = arg_tuple;
}

void set_result_arg(pfarg *result){
	g_result = result;
}