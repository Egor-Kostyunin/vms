#ifndef LOADER_H
#define LOADER_H
#include "plugin.h"

extern plugin **g_plugins;
extern unsigned short int g_count;
extern pfarg *g_arg_tuple;
extern pfarg *g_result;

BOOL load_plugin(char *plugin_name);
unsigned short int get_plugin_id(char *plugin_name);
void set_arg_tuple(pfarg *arg_tuple);
void set_result_arg(pfarg *result);
BOOL execute_by_name(unsigned short int plugin_id,char *function_name);
void unload_plugin(char *plugin_name);
#endif
