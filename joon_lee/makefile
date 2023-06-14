CC = cc

all:
	cc sender_msg_q.c -o sender_msg
	cc receiver_msg_q.c -o receiver_msg
	cc ex_pipe.c -o ex_pipe

clean:
	rm -rf sender_msg
	rm -rf receiver_msg
	rm -rf ex_pipe

re: clean all

.PHONY: all clean fclean re
