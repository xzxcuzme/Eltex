all:
	gcc shm1.c -o ./build/shm1 -lrt -pthread && gcc shm2.c -o ./build/shm2 -lrt -pthread && ./build/shm1
server:
	gcc server.c -o ./build/server -lrt -pthread && ./build/server
client: 
	gcc client.c -o ./build/client -lrt -pthread && ./build/client