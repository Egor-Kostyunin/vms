from ctypes import *

class pfarg(Union):
	_fields_ = [("intNumber", c_long),
                ("realNumber", c_double),
                ("strText", c_char_p),
				("rndData", c_void_p)]
				
PFARGPTR = POINTER(pfarg)

plugin = CDLL("../plugin.so")

task_executor = CDLL("../task_executor.so")