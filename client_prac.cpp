#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

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

    // Create a socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        std::cerr << "Error: socket creation" << std::endl;
        return -1;
    }
    inet_ntop(AF_INET, &server_addr.sin_addr, inet_addr_buf, sizeof(inet_addr_buf));
    std::cout << "Trying " << inet_addr_buf << ":" << ntohs(server_addr.sin_port) << std::endl;

    // [TODO: 서버에 연결하기]
    // - socket()으로 만든 소켓 s를 이용해서 서버와 연결한다.
    // - 이때 필요한 함수는 connect() 이다.
    // - 보통은 connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)); 형태로 사용한다.
    // - 연결이 실패하면 에러 메시지를 출력하고 종료한다.
    // - 연결이 성공하면 다음 단계로 진행하면 된다.

    std::cout << "===== Server Connected =====" << std::endl;

    int x, y;

    // [TODO: 소문자 단어 입력받기]
    // - 서버로 보낼 소문자 단어를 사용자로부터 입력받는다.
    // - msg_buffer 배열을 이용해서 입력을 받으면 된다.
    // - 예를 들면 std::cin >> msg_buffer; 같은 형태를 생각하면 된다.
    // - 이 연습에서는 소문자 단어를 서버로 보내는 흐름을 만든다.

    // [TODO: 소문자 단어를 서버로 전송하기]
    // - 입력받은 문자열을 서버로 보낸다.
    // - 여기서는 send() 함수를 사용하면 된다.
    // - 보통 send(s, msg_buffer, strlen(msg_buffer), 0); 형태로 사용한다.
    // - 전송 실패 여부도 체크해볼 수 있다.

    // [TODO: 서버로부터 대문자로 변환된 결과를 받고 출력하기]
    // - 서버가 보낸 결과 문자열을 받는다.
    // - 여기서는 recv() 함수를 사용하면 된다.
    // - 받은 문자열은 msg_buffer에 저장하고, 마지막에 '\0'을 붙여서 문자열처럼 다룬다.
    // - 마지막으로 std::cout << msg_buffer << std::endl; 로 출력하면 된다.



    close(s);
    return 0;
}
