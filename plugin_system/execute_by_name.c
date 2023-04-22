#include "loader.h"
#include <string.h>

BOOL execute_by_name(unsigned short int plugin_id,char *function_name){
	unsigned short int function_id = 0;
	
	for(unsigned short int i = 0;i < MAX_FUNCTION_COUNT;i++){
		if(g_plugins[plugin_id]->functions[i].info.type == TYPE_NOTLOAD){
			return FALSE;
		}
		
		if(strcmp(function_name,g_plugins[plugin_id]->functions[i].info.name) == 0){
			function_id = i;
			break;
		}
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_NOARG){
		g_plugins[plugin_id]->functions[function_id].addrres(NULL,NULL);
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_IN){
		if(g_arg_tuple == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(NULL,g_arg_tuple);
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_OUT){
		if(g_result == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(g_result,NULL);
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_INOUT){
		if(g_result == NULL && g_arg_tuple == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(g_result,g_arg_tuple);
	}
	return TRUE;
}