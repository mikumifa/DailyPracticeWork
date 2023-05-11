CC = g++
CFLAGS = -Wall -I /usr/include -std=c++11
LFLAGS = -L /usr/lib -lboost_system -lboost_filesystem

all: secure_client

secure_client: secure_client.o
	$(CC) $(LFLAGS) secure_client.o -o secure_client

secure_client.o: secure_client.cpp
	$(CC) $(CFLAGS) -c secure_client.cpp

clean:
	rm -f secure_client
	rm -f *.o
