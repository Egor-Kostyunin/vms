#ifndef TASK_H
#define TASK_H
#include "function.h"

#ifdef __linux__
	#include <pthread.h>
#endif

#define TASK_NOTSTART 0
#define TASK_INPROCESS 1
#define TASK_COMPLETE 2

typedef struct __task_item{
	char *plugin_name;
	char *function_name;
	pfarg *result;
	pfarg *arg_tuple;
	char status;
	BOOL success;
	__task_item *prev;
	__task_item *next;
	#ifdef __linux__
		pthread_t theard_id;
	#endif
} task;

task* new_task(char *plugin_name,char *function_name,pfarg *result,pfarg *arg_tuple);
void delete_task(task* task_ptr);
#endif