all:
	gcc Server.c -o Server
	gcc Client.c -o Client

Server: Server.c
	gcc Server.c -o Server
	./Server

Client: Client.c
	gcc Client.c -o Client
	./Client

clean:
	rm -f Client Server



