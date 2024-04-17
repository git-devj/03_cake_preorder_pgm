#include <stdio.h> // 표준 입출력 라이브러리 | printf 등 함수
#include <stdlib.h> // 표준 유틸리티 라이브러리 | atoi 등 함수
#include <string.h> // c 문자열 처리 라이브러리 | strlen 등 함수
#include <unistd.h> // 유닉스 사용 라이브러리 | write 등 함수
#include <arpa/inet.h> // 주소 조작, 변환 헤더 | inet 관련 함수
#include <sys/socket.h> // 소켓 핵심 헤더 | socket 등 함수

void error_msg(char* message); // 에러 메시지 함수 선언

// 메인 함수
int main(int argc, char* argv[]) {

    int serv_sock, clnt_sock; // 서버 소켓, 클라이언트 소켓 int 형 변수 선언
    int read_len;
    char sell_msg[1000];
    FILE* sell_lt = fopen("sell_list.txt", "a+");

    struct sockaddr_in serv_adr, clnt_adr; // 주소 관련 구조체 선언
    socklen_t clnt_adr_sz; // 구조체 크기 선언

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    } // 두 요소를 입력하지 않으면 메시지 출력하고 종료

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓은 IPv4, TCP 소켓으로 생성

    if (serv_sock == -1)
        error_msg("socket() error"); // 서버 소켓 생성 실패 시 에러 메시지 출력
    
    memset(&serv_adr, 0, sizeof(serv_adr)); // serv_adr 멤버 0으로 초기화
    serv_adr.sin_family = AF_INET; // IPv4 주소 체계
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // 컴퓨터 IP 주소 자동 할당
    serv_adr.sin_port = htons(atoi(argv[1])); // 입력한 포트로 포트 번호 저장

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) 
        error_msg("bind() error"); // 소켓에 주소 정보 할당 실패 시 메시지 출력
    
    if (listen(serv_sock, 5) == -1) 
        error_msg("listen() error"); // 연결 요청 대기 상태로 진입 실패 시 메시지 출력
    
    clnt_adr_sz = sizeof(clnt_adr); // 선언했던 구조체 크기 설정

    // 클라이언트 소켓 실행
    while (1) {

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 클라이언트 연결 요청 수락 및 서버 소켓 파일 전달, 주소 정보 담을 변수 주소 값 전달, 크기 전달

        if (clnt_sock == -1)
            error_msg("accept() error"); // 클라이언트 소켓 연결 요청 수락 실패 시 메시지 출력
        while (1) {
            read_len = read(clnt_sock, sell_msg, sizeof(sell_msg)-1);

            if(read_len == -1)
                error_msg("read() error!");

            else {
                printf("%s", sell_msg);
                memset(sell_msg, 0, sizeof(sell_msg));
            }
        }
    }
    close(clnt_sock); // 클라이언트 소켓 닫기
    close(serv_sock); // 서버 소켓 닫기
    fclose(sell_lt);

    return 0; // 종료
}

// 에러 메시지 함수
void error_msg(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
} // fputs(): 메시지를 출력, fputc(): 메시지 행 바꿈, exit(): 종료