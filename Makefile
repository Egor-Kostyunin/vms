CC = g++
DLLPOSTFIX = so
INCLUDE = ./include
SRC = ./src
PLUGINS = ./Plugins
DLLFLAGS = -fPIC -shared
PY = -I/usr/include/python3.10 -I/usr/include/python3.10 -L/usr/lib/python3.10/config-3.10-x86_64-linux-gnu -L/usr/lib/x86_64-linux-gnu -lcrypt -ldl -lm -lm -lpython3.10
build: plugin task_executor terminal uva

uvm: $(INCLUDE)/*.hpp $(SRC)/pythonvm.cpp *.cpp
	$(CC) -I $(INCLUDE) $(SRC)/pythonvm.cpp main.cpp $(PY) -o $@

plugin: $(INCLUDE)/plugin.hpp $(SRC)/plugin.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $@.$(DLLPOSTFIX) $(SRC)/plugin.cpp

task_executor: $(INCLUDE)/task_executor.hpp $(SRC)/task_executor.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $@.$(DLLPOSTFIX) $(SRC)/task_executor.cpp plugin.so

terminal: $(INCLUDE)/terminal.hpp $(SRC)/terminal.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $(PLUGINS)/$@.$(DLLPOSTFIX) $(SRC)/terminal.cpp
clean:
	rm $(PLUGINS)/*.so

.PHONY: clean
