// mach에서 메세지 전달을 설명

#include <mach/mach.h>

struct message
{
	mach_msg_header_t	header;
	int					data;
};

mach_port_t	client;
mach_port_t	server;

int main()
{
	// client code
	struct message message;

	// 헤더 구축
	message.header.msgh_size = sizeof(message);
	message.header.msgh_remote_port = server;
	message.header.msgh_local_port = client;

	// 메세지 송신
	mach_msg(&message.header, // 메세지 헤더
		MACH_SEND_MSG, // 메세지 송신
		sizeof(message), // 송신 메세지 크기
		0, // 수신 메세지 최대 크기 - 필요없음
		MACH_PORT_NULL, // 수신 포트의 이름 포트 없음 - 필요없음
		MACH_MSG_TIMEOUT_NONE, // 타임아웃 설정 없음
		MACH_PORT_NULL // 포트 없음
		);

	// server code

	mach_msg(&message.header, // 메세지 헤더
		MACH_RCV_MSG, // 메세지 송신
		0, // 송신된 메세지 크기
		sizeof(message), // 수신 메세지 최대 크기 - 필요없음
		server, // 수신 포트의 이름
		MACH_MSG_TIMEOUT_NONE, // 타임아웃 설정 없음
		MACH_PORT_NULL // 포트 없음
		);

	return 0;
}






