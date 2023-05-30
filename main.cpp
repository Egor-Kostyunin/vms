#include "plugin.hpp"
#include <iostream>

using namespace std;
using namespace plugin_api;

int main(){
	if(load("terminal") == PluginError::Success){
		cout<<"Ok"<<endl;
	}
else cuot<<"fail\n";
	cout<<(int)load("terminal")<<endl;
	return 0;
}
