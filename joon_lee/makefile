CC = cc

all:
	cc sender_msg_q.c -o sender_msg
	cc receiver_msg_q.c -o receiver_msg

clean:
	rm -rf sender_msg
	rm -rf receiver_msg

re: clean all

.PHONY: all clean fclean re
