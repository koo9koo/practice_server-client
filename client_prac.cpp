// 실습: 덧셈 요청·응답 구조를 문자열 대문자 변환 통신으로 응용
// 각 ____________에 힌트에 맞는 함수 이름이나 식 입력

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

#define MAX_BUFFER_SIZE 256
char msg_buffer[MAX_BUFFER_SIZE];

int main(int argc, char *argv[]) {
    int s;
    struct sockaddr_in server_addr;
    char inet_addr_buf[16];
    int len;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP address> <port>" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        std::cerr << "Error: invalid IP address " << argv[1] << std::endl;
        return -1;
    }
    server_addr.sin_port = htons(atoi(argv[2]));

    // IPv4용 TCP 소켓 생성
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        std::cerr << "Error: socket creation" << std::endl;
        return -1;
    }
    inet_ntop(AF_INET, &server_addr.sin_addr, inet_addr_buf, sizeof(inet_addr_buf));
    std::cout << "Trying " << inet_addr_buf << ":" << ntohs(server_addr.sin_port) << std::endl;

    // [TODO: Connect to the server]
    // 힌트: 위에서 서버 IP와 포트를 저장한 변수는 server_addr
    // connect()에는 구조체의 주소가 필요하므로 주소 연산자 &를 붙여 전달
    if (connect(s, (struct sockaddr *)____________, sizeof(server_addr)) < 0) {
        std::cerr << "Error: connection error" << std::endl;
        return -1;
    }

    std::cout << "===== Server Connected =====" << std::endl;

    std::string x;

    // [TODO: Get small letter word as an input]
    std::cout << "Enter small letters: ";
    // 힌트: getline()의 두 번째 인자는 입력한 한 줄을 저장할 문자열 변수
    // 위에서 std::string으로 선언하고, 아래 전송 준비에 사용하는 변수 선택
    std::getline(std::cin, ____________);

    // [TODO: Send small letter word to Server]
    snprintf(msg_buffer, MAX_BUFFER_SIZE, "%s", x.c_str());
    len = strlen(msg_buffer);
    // 힌트: len은 strlen()으로 구한 문자 수이며, 끝의 '\0'은 제외된 값
    // 서버에 문자열 끝도 전달하도록 len에 널 문자 크기인 1바이트 추가
    send(s, msg_buffer, ____________, 0);

    // [TODO: Receive capitalized word from Server and print it]
    // 힌트: recv()의 첫 번째 인자는 데이터를 받을 소켓
    // 위의 connect()와 send()에서 사용한 연결된 소켓 변수 선택
    len = recv(____________, msg_buffer, MAX_BUFFER_SIZE, 0);
    if (len > 0) {
        std::cout << "Capital letters: " << msg_buffer << std::endl;
    } else {
        std::cerr << "Error receiving data" << std::endl;
    }

    close(s);
    return 0;
}
