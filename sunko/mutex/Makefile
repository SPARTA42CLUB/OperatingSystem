CC = cc
SRC = error_functions.c get_num.c thread_incr.c
SRCMUTEX = error_functions.c get_num.c thread_incr_mutex.c
OBJS = $(SRC:.c=.o)
OBJSMUTEX = $(SRCMUTEX:.c=.o)

all: thread_incr thread_incr_mutex

%.o: %.c
	$(CC) -c $< -o $@

thread_incr: $(OBJS)
	$(CC) $^ -o $@

thread_incr_mutex: $(OBJSMUTEX)
	$(CC) $^ -o $@

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f thread_incr
	rm -f thread_incr_mutex
