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

    // 메시지 큐에 연결
    if ((msg_queue_id = msgget(key, 0644)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("메시지 큐에 연결되었습니다. 메시지를 수신합니다.\n");
    printf("수신을 중지하려면 Ctrl + C를 누르세요.\n");

    while (1) {
        // 메시지 큐에서 메시지 받기
        if (msgrcv(msg_queue_id, (void *)&msg, MAX_TEXT_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // 수신한 메시지 출력
        printf("수신된 메시지: %s", msg.msg_text);
    }

    return 0;
}
