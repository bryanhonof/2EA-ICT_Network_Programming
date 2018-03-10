output: server.o client.o
	clang -Wall server.o -o server
	clang -Wall client.o -o client

server.o: server.c
	clang -Wall -c server.c

client.o: client.c
	clang -Wall -c client.c

clean:
	rm *.o client server
