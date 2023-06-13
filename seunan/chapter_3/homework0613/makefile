pipe:
	gcc pipe_receiver.c -o receiver_p
	gcc pipe_sender.c -o sender_p

mq:
	gcc mq_receiver.c -o receiver_m
	gcc mq_sender.c -o sender_m

clean:
	rm -f *.o

fclean: clean
	rm -f sender_p
	rm -f sender_m
	rm -f receiver_p
	rm -f receiver_m
