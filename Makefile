СС = g++
DLLPOSTFIX = so
INCLUDE = ./include
SRC = ./src
PLUGINS = ./Plugins

build: plugin task_executor

plugin: $(INCLUDE)/plugin.hpp $(SRC)/plugin.cpp
	$(CC) -I $(INCLUDE) -o $(PLUGINS)/$@.$(DLLPOSTFIX) plugin.cpp

task_executor: $(INCLUDE)/task_executor.hpp $(SRC)/task_executor.cpp
	$(CC) -I $(INCLUDE) -o $(PLUGINS)/$@.$(DLLPOSTFIX) task_executor.cpp

clean:
	rm $(PLUGINS)/*.so

.PHONY: clean