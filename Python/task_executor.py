from ctypes import *

plugin = CDLL("../plugin.so")

task_executor = CDLL("../task_executor.so")