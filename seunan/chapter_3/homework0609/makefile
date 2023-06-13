producer.o: producer.c
	cc -c producer.c

producer: producer.o
	cc producer.o -o producer

consumer.o: consumer.c
	cc -c consumer.c

consumer: consumer.o
	cc consumer.o -o consumer

process.o: process.c
	cc -c process.c

process: process.o
	cc process.o -o process

clean:
	rm -f *.o

fclean: clean
	rm -f consumer
	rm -f producer
	rm -f process
