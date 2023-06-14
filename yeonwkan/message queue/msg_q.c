#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_SIZE 256

// 메시지 구조체
struct message {
    long mtype;
    char mtext[MAX_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // 메시지 큐 생성
    key = ftok(".", 'a');
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // 메시지 송신
    msg.mtype = 1;  // 메시지 유형
    strcpy(msg.mtext, "Hello, World!");  // 메시지 내용

    if (msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Sent message: %s\n", msg.mtext);

    // 메시지 수신
    if (msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received message: %s\n", msg.mtext);

    // 메시지 큐 삭제
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
