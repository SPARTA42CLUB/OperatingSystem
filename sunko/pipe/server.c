// server.c
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FIFO_PATH "./SUNKO-FIFO"
#define MESSAGE "Hello, FIFO"

int main(void)
{
    int pd, n;

    printf("Server =====\n");

    if (mkfifo(FIFO_PATH, 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    if ((pd = open(FIFO_PATH, O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    printf("To Client: %s\n", MESSAGE);
    n = write(pd, MESSAGE, strlen(MESSAGE) + 1);

    if (n == -1)
    {
        perror("write");
        exit(1);
    }

    close(pd);

    return 0;
}
