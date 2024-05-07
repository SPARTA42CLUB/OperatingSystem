#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void send_file(int client_sock);
char *get_filename(int client_sock);

int main()
{
	int server_socket_fd; // 서버 소켓의 파일 디스크립터
	int connection_socket; // 연결될 클라이언트의 소켓 파일 디스크립터
	struct sockaddr_in address; // 서버의 IP주소와 port번호를 저장할 구조체
	socklen_t addrlen = sizeof(address);

	// 서버의 정보 설정. sin은 socket internet의 약어
	address.sin_family = AF_INET; // 주소 체계를 나타냄. AF_INET은 IPv4를 의미
	address.sin_addr.s_addr = INADDR_ANY; // 소켓에 IP 주소를 설정. INADDR_ANY = 모든 연결을 수락하겠다(로컬 포함)
	address.sin_port = htons(8080); // host to network short의 약자. 호스트의 바이트 오더를 네트워크 바이트 오더로 변환

	// TCP 소켓을 생성하고 핸들러 반환
	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// bind()로 주소 정보를 소켓에 바인딩하고 listen()으로 연결 대기
	bind(server_socket_fd, (struct sockaddr *)&address, sizeof(address)); // 바인딩할 주소 정보를 담은 구조체와 그 크기를 넘김
	listen(server_socket_fd, 3); // 두번째 인자 backlog는 대기열의 최대 길이로 동시에 대기할 수 있는 클라이언트 연결 요청의 최대 개수를 의미한다.

	// 무한루프를 돌면서 client의 연락을 accept하고, 파일을 전송 후 연결을 닫는다.
	while (1)
	{
		connection_socket = accept(server_socket_fd, (struct sockaddr *)&address, &addrlen);
		send_file(connection_socket);
		close(connection_socket);
	}
}

void send_file(int client_sock)
{
	char buffer[1024];
	const char *filename = get_filename(client_sock);
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
		send(client_sock, not_found, strlen(not_found), 0);
		return;
	}

	// 응답의 헤더 부분
	char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
	send(client_sock, header, sizeof(header) - 1, 0);

	// 응답의 body 부분
	size_t bytes_read;
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
		send(client_sock, buffer, bytes_read, 0);
	}

	fclose(file);
}

char *get_filename(int client_sock)
{
	char buffer[1024];
	ssize_t bytes_read = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
	if (bytes_read <= 0)
		return (NULL);

	buffer[bytes_read] = '\0';

	char *line = strtok(buffer, "\r\n"); // 첫 줄만 추출
	char *method = strtok(line, " "); // GET 추출
	char *path = strtok(NULL, " "); // file name 추출

	if (method && path && strcmp(method, "GET") == 0)
	{
		if (path[0] == '/')
			path++;
		if (strlen(path) == 0)
			path = "index.html";
		return (path);
	}
	return (NULL);
}


