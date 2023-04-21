#include "loader.h"
#include <string.h>

void set_current_plugin(char *plugin_name){
	for(unsigned short int i = 0;i < g_count;i++){
		if(strcmp(plugin_name,g_plugins[i]->name) == 0){
			g_current_plugin_id = i;
			return;
		}
	}
}

void set_arg_tuple(pfarg *arg_tuple){
	g_arg_tuple = arg_tuple;
}

void set_result_arg(pfarg *result){
	g_result = result;
}
