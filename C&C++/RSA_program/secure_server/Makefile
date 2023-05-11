CC = g++
CFLAGS = -Wall -I /usr/include -std=c++11
LFLAGS = -L /usr/lib -lboost_system -lboost_filesystem

all: secure_server

secure_server: secure_server.o
	$(CC) $(LFLAGS) secure_server.o -o secure_server

secure_server.o: secure_server.cpp
	$(CC) $(CFLAGS) -c secure_server.cpp

clean:
	rm -f secure_server
	rm -f *.o
