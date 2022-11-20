BIN = binar
OBJ = object

.PHONY: all clean

all: client server

clean:
	rm -R $(BIN) $(OBJ)

client.o: raw_ip_client.c
	mkdir $(OBJ)
	gcc -c -o $(OBJ)/client.o raw_ip_client.c

server.o: raw_ip_server.c
	gcc -c -o $(OBJ)/server.o raw_ip_server.c

client: client.o
	mkdir $(BIN)
	gcc -o $(BIN)/client $(OBJ)/client.o

server: server.o
	gcc -o $(BIN)/server $(OBJ)/server.o