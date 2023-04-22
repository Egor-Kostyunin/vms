#include "plugin.h"
#include <stdlib.h>

plugin **g_plugins = NULL;
unsigned short int g_count = 0;
pfarg *g_arg_tuple;
pfarg *g_result;