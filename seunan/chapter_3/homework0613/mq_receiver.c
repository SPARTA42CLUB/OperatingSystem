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
	char receive_buffer[MESSAGE_SIZE];

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

	// 메시지 수신
	if (msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
		perror("msgrcv error");
		exit(1);
	}

	strncpy(receive_buffer, msg.mtext, sizeof(receive_buffer) - 1);
	receive_buffer[sizeof(receive_buffer) - 1] = '\0';

	printf("Received message: %s\n", receive_buffer);

	// 메시지 큐 삭제
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl error");
		exit(1);
	}

	return 0;
}
