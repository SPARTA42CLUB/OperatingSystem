CC = cc
SRC = error_functions.c get_num.c thread_incr.c
SRC_MUTEX = error_functions.c get_num.c thread_incr_mutex.c
SRC_PROD_NO_CONDVAR = prod_no_condvar.c error_functions.c
SRC_PROD_CONDVAR = prod_condvar.c error_functions.c
SRC_JOIN = thread_multijoin.c error_functions.c get_num.c
OBJS = $(SRC:.c=.o)
OBJS_MUTEX = $(SRC_MUTEX:.c=.o)
OBJS_PROD_NO_CONDVAR = $(SRC_PROD_NO_CONDVAR:.c=.o)
OBJS_PROD_CONDVAR = $(SRC_PROD_CONDVAR:.c=.o)
OBJS_JOIN = $(SRC_JOIN:.c=.o)

all: thread_incr thread_incr_mutex prod_condvar thread_multijoin

%.o: %.c
	$(CC) -c $< -o $@

thread_incr: $(OBJS)
	$(CC) $^ -o $@

thread_incr_mutex: $(OBJS_MUTEX)
	$(CC) $^ -o $@

prod_no_condvar: $(OBJS_PROD_NO_CONDVAR)
	$(CC) $^ -o $@

prod_condvar: $(OBJS_PROD_CONDVAR)
	$(CC) $^ -o $@

thread_multijoin: $(OBJS_JOIN)
	$(CC) $^ -o $@

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f thread_incr
	rm -f thread_incr_mutex
	rm -f prod_condvar
	rm -f prod_no_condvar
	rm -f thread_multijoin
