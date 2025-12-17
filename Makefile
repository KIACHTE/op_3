CC = gcc
CFLAGS = -Wall -g
RPCGEN = rpcgen

all: client server

task.h task_clnt.c task_svc.c task_xdr.c: task.x
	$(RPCGEN) -C task.x

client: client.c task_clnt.c task_xdr.c
	$(CC) $(CFLAGS) -o client client.c task_clnt.c task_xdr.c -lnsl

server: server.c queue.c task_svc.c task_xdr.c
	$(CC) $(CFLAGS) -o server server.c queue.c task_svc.c task_xdr.c -lnsl -lpthread

clean:
	rm -f client server task.h task_clnt.c task_svc.c task_xdr.c
