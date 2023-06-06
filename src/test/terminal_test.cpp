#include "terminal.hpp"

int main(){
	plugin_api::pfarg narg,args;
	narg.argValuePtr = new int[1];
	args.argValuePtr = (char*)"ls";
	args.argNext = &narg;
	terminal::exec_cmd(nullptr,&args);
	return 0;
}