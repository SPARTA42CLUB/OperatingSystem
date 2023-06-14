CC = cc
SRC = pipe.c twoWayPipe.c client.c server.c
OBJS = $(SRC:.c=.o)

all: pipe two_way_pipe client server

%.o: %.c
	$(CC) -c $^ -o $@

pipe: pipe.o
	$(CC) -o $@ $^

client: client.o
	$(CC) -o $@ $^

server: server.o
	$(CC) -o $@ $^

two_way_pipe: twoWayPipe.o
	$(CC) -o $@ $^

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f pipe two_way_pipe client server
	rm -f SUNKO-FIFO
