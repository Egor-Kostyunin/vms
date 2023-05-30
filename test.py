from ctypes import *
from Python.task_executor import pfarg
plugin = cdll.LoadLibrary('./plugin.so')
plugin.load(b'terminal')
ret = plugin.alloc_ret(c_short(1));
plugin.exec(b'terminal',b'exec_cmd',ret,plugin.create_arg_tuple(c_short(1),b'ls -a'))
print(cast(ret,POINTER(pfarg)).contents.rndData)

