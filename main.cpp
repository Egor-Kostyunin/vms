#include "pythonvm.hpp"
#include "plugin.hpp"
#include <iostream>

using namespace std;
using namespace python;

const std::list<std::string> classes = {"AuidoSpeecher"};

int main(){
	py_class pyClass;
	PythonVM pyVM;
	cout<<pyVM.LoadPyClass("audioSpeecherOOP",classes,&pyClass)<<"audioSpeecherOOP End "<<endl;
	cout<<pyVM.LoadPyClass("audioSpeecherOOP",classes,&pyClass)<<"audioSpeecherOOP End "<<endl;
	PyErr_Print();
	while(true){
		PyObject *ret = PyObject_CallMethod(pyClass.pyClasses[0],static_cast<const char*>("Next"),nullptr);
		if(ret == nullptr){
			PyErr_Print();
			continue;
		}
		PyObject *retStr = PyUnicode_AsEncodedString(ret, "utf-8", "ERROR");
		char *text = strdup(PyBytes_AS_STRING(retStr));
		if(text != nullptr){
			tcout<<text<<endl;
		}
		Py_XDECREF(ret);
		Py_XDECREF(retStr);
		delete text;
	}
	return 0;
}
