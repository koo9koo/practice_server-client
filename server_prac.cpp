// 실습: 덧셈 요청·응답 구조를 문자열 대문자 변환 통신으로 응용
// 각 ____________에 힌트에 맞는 함수 이름이나 식 입력

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

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

    // 실행 인자로 받은 서버 포트 번호 변환
    server_port = atoi(argv[1]);

    // [TODO: Create server socket]
    // 힌트: socket()의 두 번째 인자는 통신 방식
    // SOCK_STREAM은 TCP, SOCK_DGRAM은 UDP이므로 클라이언트와 같은 TCP 방식 선택
    server_socket = socket(AF_INET, ____________, 0);
    if (server_socket < 0) {
        std::cerr << "Error: socket creation" << std::endl;
        return -1;
    }

    // 서버 소켓에 IP 주소와 포트 번호 할당
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

    // [TODO: Listen for incoming connections]
    // 힌트: bind()로 주소를 할당한 뒤, accept() 전에 연결 대기 상태로 전환
    // bind(주소 할당), listen(연결 대기), accept(연결 수락) 중 해당 함수 선택
    if (____________(server_socket, 5) < 0) {
        std::cerr << "Error: listen" << std::endl;
        return -1;
    }

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            std::cerr << "Error: accept" << std::endl;
            return -1;
        }

        inet_ntop(AF_INET, &client_addr.sin_addr, inet_addr_buf, sizeof(inet_addr_buf));
        std::cout << "===== Client Connected =====" << std::endl;
        std::cout << "From " << inet_addr_buf << ":" << ntohs(client_addr.sin_port) << std::endl;

        // [TODO: Receive small letter word from client]
        // 힌트: server_socket은 연결 대기용, client_socket은 연결된 상대와의 통신용
        // recv()의 첫 번째 인자에 실제 데이터를 주고받을 소켓 선택
        len = recv(____________, msg_buffer, MAX_BUFFER_SIZE, 0);
        if (len > 0) {
            std::cout << "Received: " << msg_buffer << std::endl;
        } else {
            std::cerr << "Error receiving data" << std::endl;
            close(client_socket);
            continue;
        }

        // [TODO: Capitalize small letters]
        std::string str(msg_buffer);
        // 힌트: transform()의 마지막 인자는 각 문자에 적용할 변환 함수
        // toupper(대문자 변환), tolower(소문자 변환) 중 서버의 처리 목적에 맞는 함수 선택
        std::transform(str.begin(), str.end(), str.begin(), ::____________);

        // [TODO: Send the result to client]
        std::cout << "Sending: " << str << std::endl;
        // 첫 번째 빈칸: 변환 결과 str에 c_str()을 호출하여 전송할 문자 데이터 지정
        // 두 번째 빈칸: str.size()로 구한 길이에 널 문자 '\0'의 크기인 1바이트 추가
        // 수신 길이 len에는 널 문자가 포함되므로 변환 결과의 길이를 기준으로 계산
        send(client_socket, ____________, ____________, 0);

        // 클라이언트 연결 종료
        close(client_socket);
        std::cout << "===== Client Disconnected =====" << std::endl;
    }

    close(server_socket);
    return 0;
}
