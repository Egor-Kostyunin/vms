CC = g++
DLLPOSTFIX = so
INCLUDE = ./include
SRC = ./src
PLUGINS = ./Plugins
DLLFLAGS = -fPIC -shared

build: plugin task_executor terminal

plugin: $(INCLUDE)/plugin.hpp $(SRC)/plugin.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $@.$(DLLPOSTFIX) $(SRC)/plugin.cpp

task_executor: $(INCLUDE)/task_executor.hpp $(SRC)/task_executor.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $@.$(DLLPOSTFIX) $(SRC)/task_executor.cpp plugin.so

terminal: $(INCLUDE)/terminal.hpp $(SRC)/terminal.cpp
	$(CC) $(DLLFLAGS) -I $(INCLUDE) -o $(PLUGINS)/$@.$(DLLPOSTFIX) $(SRC)/terminal.cpp
clean:
	rm $(PLUGINS)/*.so

.PHONY: clean
