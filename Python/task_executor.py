from ctypes import *

class pfarg(Union):
	_fields_ = [("intNumber", c_long),
                ("realNumber", c_double),
                ("strText", c_char_p),
				("rndData", c_void_p)]
				
PFARGPTR = POINTER(pfarg)

#plugin = CDLL("~/uva/plugin.so")

#task_executor = CDLL("~/uva/task_executor.so")
