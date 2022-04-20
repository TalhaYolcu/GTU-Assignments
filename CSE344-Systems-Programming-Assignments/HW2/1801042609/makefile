hw2: hw2.c ProcessR_i.c
	gcc -c hw2.c -Wall
	gcc hw2.o -o processP -lm
	gcc -c ProcessR_i.c
	gcc ProcessR_i.o -o ProcessR_i
	#valgrind -v --leak-check=yes ./processP -i files/input.dat -o files/outputFile.dat	
	#./processP -i files/input.dat -o files/outputFile.dat

