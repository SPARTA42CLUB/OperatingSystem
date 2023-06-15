#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
	long long msg_type;
	char msg_text[10000];
};

int main() {
	key_t key;
	int msg_id;
	struct message msg;

	key = ftok(".", 'W');
	msg_id = msgget(key, 0666);
	msgrcv(msg_id, &msg, sizeof(msg), 1, 0);
	printf("Received message : %s\n", msg.msg_text);
	msgctl(msg_id, IPC_RMID, NULL);

	return 0;
}
