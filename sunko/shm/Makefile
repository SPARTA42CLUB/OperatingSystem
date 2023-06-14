CC = cc
SRC = consumer.c producer.c
OBJS = $(SRC:.c=.o)

all: consumer producer

%.o: %.c
	$(CC) -c $< -o $@

consumer: consumer.o
	$(CC) $^ -o $@

producer: producer.o
	$(CC) $^ -o $@

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f consumer producer

