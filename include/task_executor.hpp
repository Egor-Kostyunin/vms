#ifndef TASK_EXECUTOR_HPP
#define TASK_EXECUTOR_HPP
#include "plugin.hpp"
#ifdef __linux__
	#include <pthread.h>
#endif

namespace task_executor{
	enum TaskState{
		NotStart = 0,
		InProgress,
		Complite
	};
	
	typedef struct _task{
		char *pluginName;
		char *functionName;
		plugin_api::pfarg *ret;
		plugin_api::pfarg *arg;
		plugin_api::PluginError pluginError;
		TaskState taskState;
		#ifdef __linux__
			pthread_t thread;
		#endif
	} task;
	
	task* new_task(char* plugin_name,char *function_name,plugin_api::pfarg *ret,plugin_api::pfarg *arg);
	
	void post_task(task *task_ptr);
	
	void run();
	
	void update_tasks_state();
	
	task** get_complite(unsigned int *count);
	
	void delete_task(task *task_ptr);
};
#endif
