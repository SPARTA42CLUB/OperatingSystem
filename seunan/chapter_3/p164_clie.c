// 본문은 java로 구현, 클라이언트와 서버간의 소켓 통신을 구현하고 클라이언트가 서버로 메세지 전송하고 서버가 해당 메세지를 수신하여 출력

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* message = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 서버 주소 설정
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // 서버에 연결
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // 클라이언트에서 서버로 메시지 전송
    send(sock, message, strlen(message), 0);
    printf("Hello message sent to server\n");

    // 서버로부터 메시지 수신
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("Server message: %s\n", buffer);

    return 0;
}

/*
위 코드는 TCP 소켓을 사용하여 클라이언트와 서버 간의 통신을 구현한 예시
서버는 클라이언트의 연결 요청을 대기하고, 클라이언트는 서버에 연결하여 메시지를 전송하고 서버로부터 메시지를 수신
각 프로그램은 소켓을 생성하고 설정한 후, 서버는 연결 요청을 대기하고 클라이언트는 서버에 연결, 그 후에는 소켓을 통해 데이터를 송수신
서버는 bind() 함수를 사용하여 소켓에 주소를 바인딩하고, listen() 함수로 클라이언트의 연결 요청을 대기
클라이언트에서 연결이 요청되면 accept() 함수로 연결을 수락 이후 read() 함수로 클라이언트로부터 메시지를 수신하고, send() 함수로 서버에서 클라이언트로 메시지를 전송
클라이언트는 connect() 함수로 서버에 연결하고, send() 함수로 서버로 메시지를 전송, 그리고 read() 함수로 서버로부터 메시지를 수신하여 출력
*/
