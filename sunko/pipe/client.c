// client.c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FIFO_PATH "./SUNKO-FIFO"

int main(void)
{
    int pd, n;
    char inmsg[80];

    if ((pd = open(FIFO_PATH, O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    printf("Client =====\n");
    write(1, "From Server :", 13);

    while ((n = read(pd, inmsg, sizeof(inmsg))) > 0)
        write(1, inmsg, n);

    if (n == -1)
    {
        perror("read");
        exit(1);
    }

    write(1, "\n", 1);
    close(pd);

    return 0;
}
