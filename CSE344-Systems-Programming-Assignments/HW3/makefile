hw3:
	gcc -c -Wall hw3_named.c named_implementation.c
	gcc -c -Wall unnamed_implementation.c hw3_unnamed.c
	gcc hw3_named.o -o hw3_named -lrt -lpthread
	gcc hw3_unnamed.o -o hw3_unnamed -lrt -lpthread
	#valgrind --leak-check=yes --track-origins=yes ./hw3_named -i input.txt -n name
	#valgrind --leak-check=yes ./hw3_unnamed -i input.txt
