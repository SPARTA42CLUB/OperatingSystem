CC = cc

all:
	cc fork_exec.c -o fork_exec
	cc shared_mem.c -o shared_mem

clean:
	rm -rf fork_exec
	rm -rf shared_mem

re: fclean all

.PHONY: all clean fclean re