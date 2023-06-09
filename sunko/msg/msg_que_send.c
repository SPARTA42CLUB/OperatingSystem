#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long	mytype;
	char	mtext[80];
};

int main(void)
{
	key_t	key;
	int		msgid;
	struct	mymsgbuf mesg;

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT | 0644);
	if (msgid == -1){
		perror("msgget");
		exit(1);
	}
	mesg.mytype = 1;
	strcpy(mesg.mtext, "Message Q Test");
	if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1){
		perror("msgsnd");
		exit(1);
	}
}
