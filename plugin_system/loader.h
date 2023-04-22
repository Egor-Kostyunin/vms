#ifndef LOADER_H
#define LOADER_H
#include "plugin.h"

extern plugin **g_plugins;
extern unsigned short int g_count;

BOOL load_plugin(char *plugin_name);
unsigned short int get_plugin_id(char *plugin_name);
BOOL execute_by_name(unsigned short int plugin_id,char *function_name,pfarg *result,pfarg *arg_tuple);
void unload_plugin(char *plugin_name);
#endif
