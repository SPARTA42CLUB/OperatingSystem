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

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f fork
	rm -f mmap
	rm -f mmap_fork

