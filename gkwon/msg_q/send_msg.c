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

    // Create the message queue
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // Messages are sent
    while(running) {
        printf("Enter some text: ");
        fgets(data.text, 512, stdin);
        data.msg_type = 1;

        if(msgsnd(msgid, (void*)&data, sizeof(data), 0) == -1) {
            fprintf(stderr, "msgsnd failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        if(strncmp(data.text, "end", 3) == 0) {
            running = 0;
        }
    }
    exit(EXIT_SUCCESS);
}
