hw4:
	gcc hw5.c -Wall -Wextra -lrt -lpthread -lm -o hw5 

run:
	./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output -n 3 -m 4
run_2:
	./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output2 -n 3 -m 6
run_3:
	./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output3 -n 3 -m 16
run_4:
	./hw5 -i data9 -j data10 -o output6x8.csv -n 8 -m 6
run_5:
	./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output -n 3 -m 2
run_wrong:
	./hw5 -i doesnotexists -j doesnotexists2 -o out -n 3 -m 2

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output -n 3 -m 4
leak_2:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./hw5 -i data9 -j data10 -o output6x8.csv -n 8 -m 6	
leak_3:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output3 -n 3 -m 16


leak_4:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./hw5 -i data9 -j data10 -o output6x8.csv -n 8 -m 6	
leak_5:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./hw5 -i examples/input1.txt -j examples/input2.txt -o examples/output -n 3 -m 2



clean:
	rm -f *.o
	rm -f hw5
	rm -f implementation
