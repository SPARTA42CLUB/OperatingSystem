CC = cc
SRC = fork.c mmap.c mmap_fork.c use_shm.c create_shm.c 
OBJS = $(SRCS:.c=.o)



all: fork mmap mmap_fork use_shm create_shm 

%.o: %.c
	$(CC) -c $< -o $@

fork: fork.o
	$(CC) -o $@ $<

mmap: mmap.o
	$(CC) -o $@ $<

mmap_fork: mmap_fork.o
	$(CC) -o $@ $<
	 
use_shm: use_shm.o
	$(CC) -o $@ $<

create_shm: create_shm.o
	$(CC) -o $@ $<
	

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f fork
	rm -f mmap
	rm -f mmap_fork
	rm -f create_shm
	rm -f use_shm

