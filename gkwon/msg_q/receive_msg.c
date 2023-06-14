#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct msg_st {
    long int msg_type;
    char text[512];
};

int main() {
    int running = 1;
    struct msg_st data;
    int msgid = -1;
    long int msg_to_receive = 0;

    // Create the message queue
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // Messages are received
    while(running) {
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("You wrote: %s", data.text);
        if(strncmp(data.text, "end", 3) == 0) {
            running = 0;
        }
    }
    // Finally, the message queue is deleted.
    if(msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
