CC = gcc
DLLFLAGS = -shared -fPIC
DLLPOSTFIX = so

plugin_system:
	$(CC) $(DLLFLAGS) -o $@.$(DLLPOSTFIX) 

plugin_system_o: plugin_system/*.h plugin_system/*.c
	cd obj/plugin_system || $(CC) -c $(wildcard plugin_system/*.c)