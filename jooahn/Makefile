SRC_FORK = fork_exec.c
OBJ_FORK = fork_exec.o

SRC_SHM = shared_memory.c
OBJ_SHM = shared_memory.o

FORK = fork
SHM = shared_memory

all: $(FORK) $(SHM)

$(FORK): $(OBJ_FORK)
	cc -o $@ $^

$(SHM): $(OBJ_SHM)
	cc -o $@ $^

%.o: %.c
	cc -c $< -o $@

clean:
	rm -rf $(OBJ_FORK) $(OBJ_SHM) $(FORK) $(SHM)

re: 
	make clean
	make all

fork: $(FORK)

shm: $(SHM)
