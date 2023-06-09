fork.o: fork.c
	cc -c fork.c

fork: fork.o
	cc fork.o -o fork

mmap.o: mmap.c
	cc -c mmap.c

mmap: mmap.o
	cc mmap.o -o mmap

mmap_fork.o: mmap_fork.c
	cc -c mmap_fork.c

mmap_fork: mmap_fork.o
	cc mmap_fork.o -o mmap_fork

use_shm.o: use_shm.c
	cc -c use_shm.c

use_shm: use_shm.o
	cc use_shm.o -o use_shm

create_shm.o: create_shm.c
	cc -c create_shm

create_shm: create_shm.o
	cc create_shm.o -o create_shm

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f fork
	rm -f mmap
	rm -f mmap_fork
	rm -f create_shm
	rm -f use_shm

