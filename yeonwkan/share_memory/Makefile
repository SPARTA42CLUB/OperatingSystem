CC = cc

all:
	cc counter.c -o counter
	cc exec.c -o exec
	cc fork.c -o fork
	cc show_count.c -o show_count
	cc delete.c -o delete

clean:
	rm -rf show_count
	rm -rf exec
	rm -rf fork
	rm -rf counter
	rm -rf delete

re: fclean all

.PHONY: all clean fclean re
