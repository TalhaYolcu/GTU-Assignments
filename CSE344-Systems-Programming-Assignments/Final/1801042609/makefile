
all:
	make client
	make server
	make servant

client:
	gcc -Wall client.c -o client -lpthread -lrt

server:
	gcc -Wall server.c -o server -lpthread -lrt

servant:
	gcc -Wall servant.c -o servant -lpthread -lrt

run_client:
	./client -r requestFile -q 33000 -s 127.0.0.1

run_server:
	./server -p 33000 -t 11 #&

run_servant:
	./servant -d dataset -c 1-9 -r 127.0.0.1 -p 33000 #&

valgrind_run_client:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./client -r requestFile -q 33000 -s 127.0.0.1

valgrind_run_server:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./server -p 33000 -t 11 #&

valgrind_run_servant:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./servant -d dataset -c 1-9 -r 127.0.0.1 -p 33000 #&

clean:
	rm -f *.o
	rm -f client
	rm -f server
	rm -f servant

