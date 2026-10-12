#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 256
char msg_buffer[MAX_BUFFER_SIZE];

int main(int argc, char *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char inet_addr_buf[16];
    socklen_t client_addr_len = sizeof(client_addr);
    int server_port;
    int len, i;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return -1;
    }

    // Get server port number
    server_port = atoi(argv[1]);

    // [TODO: 서버 소켓 생성하기]
    // - 서버용 소켓을 생성한다.
    // - 이 단계는 socket() 함수를 호출하는 부분이다.
    // - 보통은 socket(AF_INET, SOCK_STREAM, 0); 형태로 만든다.
    // - 생성이 실패하면 에러 메시지를 출력하고 종료한다.

    // Bind an address IP:Port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: bind" << std::endl;
        return -1;
    }

    inet_ntop(AF_INET, &server_addr.sin_addr, inet_addr_buf, sizeof(inet_addr_buf));
    std::cout << "Addr: " << inet_addr_buf << std::endl;
    std::cout << "Port: " << ntohs(server_addr.sin_port) << std::endl;

    // [TODO: 연결 요청을 기다리기]
    // - bind() 이후에 서버가 클라이언트 연결을 기다리도록 설정한다.
    // - 이때 listen() 함수를 사용한다.
    // - 보통 listen(server_socket, 5); 형태로 작성한다.
    // - 이후 accept()를 호출해서 연결을 받아들이면 된다.

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            std::cerr << "Error: accept" << std::endl;
            return -1;
        }

        inet_ntop(AF_INET, &client_addr.sin_addr, inet_addr_buf, sizeof(inet_addr_buf));
        std::cout << "===== Client Connected =====" << std::endl;
        std::cout << "From " << inet_addr_buf << ":" << ntohs(client_addr.sin_port) << std::endl;

        // [TODO: 클라이언트가 보낸 소문자 단어 받기]
        // - client_socket을 통해서 문자열을 수신한다.
        // - recv() 함수를 사용한다.
        // - 보통 recv(client_socket, msg_buffer, sizeof(msg_buffer) - 1, 0); 형태로 받는다.
        // - 받은 길이를 저장하고, 문자열 끝에 '\0'을 붙여서 처리한다.

        // [TODO: 소문자를 대문자로 변환하기]
        // - 받은 문자열을 소문자에서 대문자로 바꾼다.
        // - 반복문을 돌면서 각 문자를 검사한다.
        // - 소문자인 경우 'a'~'z' 범위를 판별해서 대문자로 바꾸면 된다.
        // - 예를 들면 문자 값에서 32를 빼면 대문자가 된다.

        // [TODO: 변환된 결과를 클라이언트에게 보내기]
        // - 변환된 문자열을 다시 client_socket으로 전송한다.
        // - 이때 send() 함수를 사용한다.
        // - 보통 send(client_socket, msg_buffer, strlen(msg_buffer), 0); 형태로 작성한다.
        // - 전송이 끝나면 연결을 종료한다.

        // Connection Close
        close(client_socket);
        std::cout << "===== Client Disconnected =====" << std::endl;
    }

    close(server_socket);
    return 0;
}
