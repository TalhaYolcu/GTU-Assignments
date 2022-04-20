mid: get_num.c error_functions.c client.c serverY.c
	gcc -c -Wall get_num.c error_functions.c client.c serverY.c become_daemon.c serverZ.c
	gcc  get_num.o error_functions.o client.o -o client 
	gcc  become_daemon.o get_num.o error_functions.o serverY.o -o serverY 
	gcc get_num.o error_functions.o serverZ.o -o serverZ -lrt -lpthread
