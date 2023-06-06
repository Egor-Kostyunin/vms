#include "plugin.hpp"

int main(){
	plugin_api::pfarg narg,args;
	narg.argValuePtr = new int[1];
	args.argValuePtr = (char*)"ls";
	args.argNext = &narg;
	plugin_api::load("terminal");
	plugin_api::exec("terminal","exec_cmd",nullptr,&args);
	plugin_api::unload("terminal");
}