CC = gcc
DLLFLAGS = -shared
DLLPOSTFIX = so

plugin_system: plugin_system_o 
	$(CC) $(DLLFLAGS) -o $@.$(DLLPOSTFIX) obj/plugin_system/*.o 

plugin_system_o: plugin_system/*.h plugin_system/*.c
	$(CC) -fPIC -c plugin_system/*.c
	mv *.o obj/plugin_system