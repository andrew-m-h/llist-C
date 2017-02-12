CFLAGS := $(CFLAGS) -std=c90 -O3 -Wall -Wextra -Werror


llist_test: src/llist.c include/llist.h include/llist.def example/main.c example/llist_usertype.def example/custom.h
	cc $(CFLAGS) -Iinclude/ -Iexample/ -o llist_test src/llist.c example/main.c 

llist.so: src/llist.c include/llist.h include/llist.def
	cc $(CFLAGS) -Iinclude/ -shared -fPIC -o llist.so src/llist.c
clean:
	rm -f llist.so llist_test


