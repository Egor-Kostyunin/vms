#ifndef PYTHONVM_HPP
#define PYTHONVM_HPP
#include "Python.h"
#include <list>
#include <vector>
#include <string>

namespace python{
	typedef struct _py_class{
		PyObject *pyModule;
		PyObject *pyModuleDict;
		std::vector<PyObject*> pyClasses;
	} py_class;

	class PythonVM{
	public:
		PythonVM();
		bool LoadPyClass(std::string modul_name,std::list<std::string> classes_names,py_class *py_class_ptr);
		
		~PythonVM();
	};
};
#endif