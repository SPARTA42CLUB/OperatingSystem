CC = cc
SRC = message_queue_example.c recevie.c msg_que_send.c msg_que_receive.c
OBJS = $(SRC:.c=.o)

all: message_queue_example message_queue_recevie msg_que_receive msg_que_send

%.o: %.c
	$(CC) -c $^ -o $@

message_queue_example: message_queue_example.o
	$(CC) -o $@ $^

message_queue_recevie: recevie.o
	$(CC) -o $@ $^

msg_que_send: msg_que_send.o
	$(CC) -o $@ $^

msg_que_receive: msg_que_receive.o
	$(CC) -o $@ $^

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f message_queue_example message_queue_recevie msg_que_receive msg_que_send
