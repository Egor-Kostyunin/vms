#include "task_executor.hpp"
#include <cstdlib>
#include <list>

namespace task_executor{
	std::list<task*> tasks;
	std::list<task*> complite_tasks;
	
	void exec_theard(void *task_ptr){
		reinterpret_cast<task*>(task_ptr)->pluginError = plugin_api::exec(reinterpret_cast<task*>(task_ptr)->pluginName,
																		  reinterpret_cast<task*>(task_ptr)->functionName,
																		  reinterpret_cast<task*>(task_ptr)->ret,
																		  reinterpret_cast<task*>(task_ptr)->arg);
	}
	
	task* new_task(char* plugin_name,char *function_name,plugin_api::pfarg *ret,plugin_api::pfarg *arg){
		task *task_ptr = (task*)std::calloc(1,sizeof(task));
		task_ptr->pluginName = plugin_name;
		task_ptr->functionName = function_name;
		task_ptr->ret = ret;
		task_ptr->ret = arg;
		return task_ptr;
	}
	
	void post_task(task *task_ptr){
		tasks.push_back(task_ptr);
	}
	
	void run(){
		for(auto it = tasks.begin();it != tasks.end();++it){
			if((*it)->taskState == TaskState::NotStart){
				(*it)->taskState = TaskState::InProgress;
				ptheard_create(&(*it)->theard,nullptr,exec_theard,(*it));
			}
		}
	}
	
	void move_complit_to_other_list(){
		for(auto it = tasks.begin();it != tasks.end();){
			if((*it)->taskState == TaskState::Complite){
				complite_tasks.push_back((*it));
				it = tasks.erase(it);
			}
			else{
				++it;
			}
		}
	}
	
	void update_tasks_state(){
		for(auto it = tasks.begin();it != tasks.end();++it){
			if((*it)->taskState == TaskState::InProgress){
				int retcode = 0;
				if(pthread_tryjoin_np((*it)->theard,&retcode) == 0){
					(*it)->taskState = TaskState::Complite;
				}
			}
		}
		move_complit_to_other_list();
	}
	
	task** get_complite(unsigned int *count){
		*count = complite_tasks.size();
		unsigned int i = 0;
		task **task_ptr = (task**)std::calloc(complite_tasks.size(),sizeof(task*));
		for(auto it = complite_tasks.begin();it != complite_tasks.end();++it){
			task_ptr[i] = (*it);
			i++;
		}
		complite_tasks.erase(complite_tasks.begin(),complite_tasks.end());
		return task_ptr;
	}
	
	void delete_task(task *task_ptr){
		std::free(task_ptr);
	}
};