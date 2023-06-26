#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_SIZE 1024

struct message {
	long mtype;
	char mtext[MESSAGE_SIZE];
};

int main() {
	key_t key;
	int msqid;
	struct message msg;
	char message_text[MESSAGE_SIZE];

	// 키 생성
	if ((key = ftok(".", 'x')) == -1) {
		perror("ftok error");
		exit(1);
	}

	// 메시지 큐 생성 또는 연결
	if ((msqid = msgget(key, IPC_CREAT | 0666)) == -1) {
		perror("msgget error");
		exit(1);
	}

	// 메시지 입력
	printf("Enter a message: ");
	fgets(message_text, sizeof(message_text), stdin);

	// 메시지 속성 설정
	msg.mtype = 1;
	strncpy(msg.mtext, message_text, sizeof(msg.mtext));

	// 메시지 전송
	if (msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1) {
		perror("msgsnd error");
		exit(1);
	}

	printf("Message sent: %s", message_text);

	return 0;
}
