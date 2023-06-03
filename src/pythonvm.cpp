#include "pythonvm.hpp"

namespace python{
	PythonVM::PythonVM(){
		Py_Initialize();
	}
	bool PythonVM::LoadPyClass(std::string modul_name,std::list<std::string> classes_names,py_class *py_class_ptr){
		//Импорт модуля
		py_class_ptr->pyModule = PyImport_ImportModule(modul_name.c_str());
		if (py_class_ptr->pyModule == nullptr) {
			delete py_class_ptr;
            return false;
        }
		//Получение словаря модуля
		py_class_ptr->pyModuleDict = PyModule_GetDict(py_class_ptr->pyModule);
		if (py_class_ptr->pyModuleDict == nullptr) {
			Py_XDECREF(py_class_ptr->pyModule);
			delete py_class_ptr;
            return false;
        }
		//Получение класса
		for(auto class_name : classes_names){
			PyObject *pyClass = PyDict_GetItemString(py_class_ptr->pyModuleDict,class_name.c_str());
			if (pyClass == nullptr) {
				Py_XDECREF(py_class_ptr->pyModule);
				Py_XDECREF(py_class_ptr->pyModuleDict);
				delete py_class_ptr;
				return false;
			}
			if(!PyCallable_Check(pyClass)){
				Py_XDECREF(py_class_ptr->pyModule);
				Py_XDECREF(py_class_ptr->pyModuleDict);
				delete py_class_ptr;
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