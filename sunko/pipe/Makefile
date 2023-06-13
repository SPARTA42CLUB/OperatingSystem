CC = cc
SRC = pipe.c twoWayPipe.c
OBJS = $(SRC:.c=.o)

all: pipe two_way_pipe

%.o: %.c
	$(CC) -c $^ -o $@

pipe: pipe.o
	$(CC) -o $@ $^

two_way_pipe: twoWayPipe.o
	$(CC) -o $@ $^

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f pipe two_way_pipe
