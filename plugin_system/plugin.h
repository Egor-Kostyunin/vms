#ifndef PLUGIN_H
#define PLUGIN_H
#include "function.h"

#ifdef __linux__
	typedef void* dlllib;
#endif

#define MAX_FUNCTION_COUNT 512

typedef struct {
	function_info info;
	function addrres;
} plugin_function;

typedef struct {
	char *name;
	dlllib lib;
	plugin_function functions[MAX_FUNCTION_COUNT];
	unsigned short int count;
} plugin;

typedef function_info* (*export_function)(unsigned short int *count);
#endif