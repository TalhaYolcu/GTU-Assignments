hw4: header.h implementation.c hw4.c
	gcc -c -Wall hw4.c implementation.c
	gcc hw4.o -o hw4 -lrt -lpthread

run:
	./hw4 -C 5 -N 2 -F input2.txt
	
leak:
	valgrind --leak-check=yes --track-origins=yes --show-reachable=yes ./hw4 -C 5 -N 2 -F input2.txt

clean:
	rm -f *.o
	rm -f hw4
	rm -f implementation