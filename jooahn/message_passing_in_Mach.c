#include <mach/mach.h>

struct message {
	mach_msg_header_t header;
	int data;
};

mach_port_t client;
mach_port_t server;

/* client code */

struct message message;

// 헤더를 구축
message.header.msgh_size = sizeof(message);
message.header.msgh_remote_port = server;
message.header.msgh_local_port = client;

// 메시지를 송신한다
mach_msg(&message.header, // 메시지 헤더
	MACH_SEND_MSG, // 메시지 송신
	sizeof(message), // 송신 메시지 크기
	0, // 수신 메시지의 최대 크기
	MACH_PORT_NULL, // 수신 포트의 이름 포트
	MACH_MSG_TIMEOUT_NONE, // 타임아웃 설정
	MACH_PORT_NULL // 포트 없음
);


/* server code */

struct message message;

// 메시지를 수신한다
mach_msg(&message.header,
	MACH_RCV_MSG, 
	0, 
	sizeof(message),
	server,
	MACH_MSG_TIMEOUT_NONE,
	MACH_PORT_NULL
);
