CC = cc

R_SOURCE = receive_msg.c
S_SOURCE = send_msg.c

all :
	$(CC) $(R_SOURCE) -o receive_msg
	$(CC) $(S_SOURCE) -o send_msg
sm :
	

fclean :
	rm -f receive_msg
	rm -f send_msg

re : fclean all

.PHONY: all re clean