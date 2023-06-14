#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT_SIZE 100

struct message {
    long msg_type;
    char msg_text[MAX_TEXT_SIZE];
};

int main() {
    int msg_queue_id;
    struct message msg;
    key_t key;

    // 메시지 큐 키 생성
    if ((key = ftok("message_queue_example.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // 메시지 큐 생성
    if ((msg_queue_id = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("메시지 큐가 생성되었습니다. 메시지를 입력하세요.\n");
    printf("Ctrl + C를 누르면 종료합니다.\n");

    while (1) {
        // 메시지 입력 받기
        printf("메시지: ");
        fgets(msg.msg_text, MAX_TEXT_SIZE, stdin);
        msg.msg_type = 1;

        // 메시지 큐에 보내기
        if (msgsnd(msg_queue_id, (void *)&msg, MAX_TEXT_SIZE, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
