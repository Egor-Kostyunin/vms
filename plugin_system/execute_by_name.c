#include "loader.h"
#include <string.h>

BOOL execute_by_name(unsigned short int plugin_id,char *function_name,pfarg *result,pfarg *arg_tuple){
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
		if(arg_tuple == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(NULL,arg_tuple);
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_OUT){
		if(result == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(result,NULL);
	}
	
	if(g_plugins[plugin_id]->functions[function_id].info.type == TYPE_INOUT){
		if(result == NULL && arg_tuple == NULL){
			return FALSE;
		}
		
		g_plugins[plugin_id]->functions[function_id].addrres(result,arg_tuple);
	}
	return TRUE;
}