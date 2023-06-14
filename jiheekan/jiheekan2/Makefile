CC = gcc
CFLAGS = -Wall -Wextra

all: m_receive m_send pipe

m_receive: m_receive.c
	$(CC) $(CFLAGS) -o m_receive m_receive.c

m_send: m_send.c
	$(CC) $(CFLAGS) -o m_send m_send.c

pipe: pipe.c
	$(CC) $(CFLAGS) -o pipe pipe.c

clean:
	rm -f m_receive m_send pipe
