#include "terminal.hpp"

using namespace treminal;

int main(){
	exec_cmd(nullptr,plugin_api::create_arg_tuple(2,(plugin_api::pfarg)"ls",(plugin_api::pfarg)4096));
	return 0;
}
