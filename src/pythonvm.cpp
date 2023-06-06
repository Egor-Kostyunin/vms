#include "pythonvm.hpp"
#include <iostream>
namespace python{
	PythonVM::PythonVM(){
		Py_Initialize();
	}
	bool PythonVM::LoadPyClass(std::string modul_name,std::list<std::string> classes_names,py_class *py_class_ptr){
		std::cout<<"StartLoad"<<std::endl;
		// Загрузка модуля sys
        	PyObject *sys = PyImport_ImportModule("sys");
        	PyObject *sys_path = PyObject_GetAttrString(sys, "path");
        	// Путь до наших исходников Python
        	PyObject *folder_path = PyUnicode_FromString((const char*) "./Python");
        	PyList_Append(sys_path, folder_path);
		//Импорт модуля
		py_class_ptr->pyModule = PyImport_ImportModule(modul_name.c_str());
		if (py_class_ptr->pyModule == nullptr) {
            return false;
        }
		//Получение словаря модуля
		py_class_ptr->pyModuleDict = PyModule_GetDict(py_class_ptr->pyModule);
		if (py_class_ptr->pyModuleDict == nullptr) {
			Py_XDECREF(py_class_ptr->pyModule);
            return false;
        }
		//Получение класса
		for(auto class_name : classes_names){
			PyObject *pyClass = PyDict_GetItemString(py_class_ptr->pyModuleDict,class_name.c_str());
			if (pyClass == nullptr) {
				Py_XDECREF(py_class_ptr->pyModule);
				Py_XDECREF(py_class_ptr->pyModuleDict);
				return false;
			}
			if(!PyCallable_Check(pyClass)){
				Py_XDECREF(py_class_ptr->pyModule);
				Py_XDECREF(py_class_ptr->pyModuleDict);
				return false;
			}
			py_class_ptr->pyClasses.push_back(PyObject_CallObject(pyClass, NULL));
		}
		return true;
	}
	PythonVM::~PythonVM(){
		Py_Finalize();
	}
};
