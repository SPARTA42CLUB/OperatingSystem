#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
	long long msg_type;
	char msg_text[1000];
};

int main() {
	key_t key;
	int msg_id;
	struct message msg;

	key = ftok(".", 'W');
	msg_id = msgget(key, 0666 | IPC_CREAT);
	msg.msg_type = 1;
	strcpy(msg.msg_text, "Hello world!");
	msgsnd(msg_id, &msg, sizeof(msg), 0);

	while (1) {
		if (getchar() == 'q')
			break;
	}
	msgctl(msg_id, IPC_RMID, NULL);

	return 0;
}
