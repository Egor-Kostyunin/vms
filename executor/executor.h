#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "task.h"
#include "function.h"

#define MAX_TASK_COUNT 512

extern task *g_task_list;
extern task *g_task_last;
extern unsigned short int g_task_count;

typedef struct{ 
	char *plugin_name;
	char *function_name;
	pfarg *result;
	BOOL success;
} complete_task;

BOOL start_task(task *task_ptr);

complete_task* get_complete(unsigned short int *count);

void* theard_execute(void *param);
#endif