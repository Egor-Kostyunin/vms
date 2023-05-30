#include "terminal.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace treminal{
	plugin_api::function_info functions[1] = {(plugin_api::function_info){"exec_cmd",plugin_api::FunctionType::InOut}};
	plugin_api::function_info* plugin_export(unsigned short int *count){
		*count = 1;
		return functions;
	}
	plugin_api::PluginError exec_cmd(plugin_api::pfarg *ret,plugin_api::pfarg *arg){
	        cout<<arg<<" "<<ret<<endl;
		return plugin_api::PluginError::Success;
	}
};
