CC = gcc
DLLFLAGS = -shared -fPIC
DLLPOSTFIX = so

plugin_system:
	$(CC) $(DLLFLAGS) -o $@.$(DLLPOSTFIX) 

plugin_system_o: plugin_system/*.h plugin_system/*.c
	$(CC) -o $(patsubst %.c,obj/%.o,$(wildcard plugin_system/*.c)) -c $(wildcard plugin_system/*.c)