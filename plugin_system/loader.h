#ifndef LOADER_H
#define LOADER_H
#include "plugin.h"

extern plugin **g_plugins;
extern unsigned short int g_count;
extern unsigned short int g_current_plugin_id;
extern pfarg *g_arg_tuple;
extern pfarg *g_result;

BOOL load_plugin(char *plugin_name);
void set_current_plugin(char *plugin_name);
void set_arg_tuple(pfarg *arg_tuple);
void set_result_arg(pfarg *result);
BOOL execute_by_name(char *function_name);
void unload_plugin(char *plugin_name);
#endif
