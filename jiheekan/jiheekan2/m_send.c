#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100

struct message {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // 메시지 큐 생성
    key = ftok(".", 'q');
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // 메시지 전송
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello, receiver!");
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    return 0;
}
