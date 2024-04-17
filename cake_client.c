#include <stdio.h> // 표준 입출력 라이브러리 | printf 등 함수
#include <stdlib.h> // 표준 유틸리티 라이브러리 | atoi 등 함수
#include <string.h> // c 문자열 처리 라이브러리 | strlen 등 함수
#include <unistd.h> // 유닉스 사용 라이브러리 | write 등 함수
#include <arpa/inet.h> // 주소 조작, 변환 헤더 | inet 관련 함수
#include <sys/socket.h> // 소켓 핵심 헤더 | socket 등 함수

void error_msg(char* message); // 에러 메시지 함수 선언

// 메인 함수
int main(int argc, char* argv[]) {
    int clnt_sock; // 클라이언트 소켓 int 형 변수 선언

    char menu; // 메뉴를 받기 위한 char형 변수

    char basket[10000] = ""; // 메뉴를 담아서 출력하기 위한 char 배열
    char* sell_list[8] = {"러브러브초코 15cm ", "마이넘버원 18cm ", "우유듬뿍 생크림케이크 3호 ", "해피스마일 13cm ", "호두아몬드파티 24cm ", "클래식 쇼콜라 18cm ", "딸기마블쉬폰 15cm ",
                        "클래식 쇼콜라 18cm "}; // 케이크를 담기 위한 메뉴 char 배열
    char sell_msg[100000] = "";

    int visit = 1; // 첫 방문을 확인하기 위한 int형 변수
    int price = 0; // 가격을 출력하기 위한 int형 변수
    int check_sum = 0; // 결제를 확인하기 위한 int형 변수
    int year = 2023, month = 1, day = 1; // 예약 일을 받기 위한 int형 변수

    struct sockaddr_in serv_adr; // 주소 관련 구조체 선언

    if(argc != 3) { 
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    } // 세 요소를 입력하지 않으면 메시지 출력하고 종료

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0); // 클라이언트 소켓은 IPv4, TCP 소켓으로 생성
    
    if(clnt_sock == -1)
        error_msg("socket() error!"); // 서버 소켓 실패 시 에러 메시지 출력

    memset(&serv_adr, 0, sizeof(serv_adr)); // serv_adr 멤버 0으로 초기화
    serv_adr.sin_family = AF_INET; // IPv4 주소 체계
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // 입력한 IP 주소 할당
    serv_adr.sin_port = htons(atoi(argv[2])); // 입력한 포트로 포트 번호 저장

    if(connect(clnt_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_msg("connect() error!"); // 연결 요청 실패 시 메시지 출력

    while(1) {
        if(visit == 1) {
            printf("어서 오세요! 불타는 베이커리입니다~\n\n");
            visit--;
        } // 첫 방문이면 첫 방문 메시지 출력하고 첫 방문 해제

        else {
            printf("1. 러브러브초코 15cm: 24,000원 / 2. 마이넘버원 18cm 33,000원 / 3. 우유듬뿍 생크림케이크 3호 39,000원 / 4. 해피스마일 13cm 25,000원\n");
            printf("5. 호두아몬드파티 24cm: 33,000원 / 6. 클래식 쇼콜라 18cm 24,000원 / 7. 딸기마블쉬폰 15cm 29,000원 / 8. 초코쉬폰 15cm 29,000원\n");
            printf("P. 계산 하기 / X. 종료하기\n\n");

            printf("메뉴를 골라주세요: "); // 메뉴 및 항목 전부 출력

            scanf(" %c", &menu); // 메뉴 입력

            switch (menu) {
                case '1':
                    system("clear");
                    printf("러브러브초코 15cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[0]);
                    price += 24000;
                    break; // 스위치 문 | 1번인 러브러브초코 15cm를 골랐을 때 터미널을 비움, 선택 메시지 출력, basket에 sell_list[0] = "러브러브초코 15cm\n"을 붙여 넣음, 가격은 24000원이 더해짐 
                    // | 스위치 문이므로 이후 생략
                case '2':
                    system("clear");
                    printf("마이넘버원 18cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[1]);
                    price += 33000;
                    break;
                case '3':
                    system("clear");
                    printf("우유듬뿍 생크림케이크 3호를 골랐습니다.\n\n");
                    strcat(basket, sell_list[2]);
                    price += 39000;
                    break;
                case '4':
                    system("clear");
                    printf("해피스마일 13cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[3]);
                    price += 25000;
                    break;
                case '5':
                    system("clear");
                    printf("호두아몬드파티 24cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[4]);
                    price += 33000;
                    break;
                case '6':
                    system("clear");
                    printf("클래식 쇼콜라 18cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[5]);
                    price += 24000;
                    break;
                case '7':
                    system("clear");
                    printf("딸기마블쉬폰 15cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[6]);
                    price += 29000;
                    break;
                case '8':
                    system("clear");
                    printf("초코쉬폰 15cm를 골랐습니다.\n\n");
                    strcat(basket, sell_list[7]);
                    price += 29000;
                    break;
                case 'P':
                case 'p':
                    if(price == 0) {
                        system("clear");
                        printf("고르신 품목이 없습니다.\n");
                        sleep(2);
                        system("clear");
                        break;
                    } // 소문자, 대문자 구분 없이 결제함 | 터미널 비움 | 고른 게 없을 때는 메시지 출력 | 보여주고 읽을 수 있게 기다렸다가 다시 비움
                    else {
                        printf("계산 창을 불러옵니다.\n\n");
                        sleep(1);
                        system("clear");
                        printf("고르신 품목은 \n%s\n\n", basket);
                        printf("가격은 %d원입니다.\n\n", price);
                        // 고른 게 있을 때는 메시지 출력 | 잠시 기다렸다가 품목과 가격만 출력

                        printf("맞으시면 1을 입력해주시고 메뉴로 돌아가시려면 다른 것을 입력해주세요: \n");
                        scanf("%d", &check_sum);
                        if(check_sum == 1) {
                            system("clear");
                            printf("수령년을 입력해주세요: \n");
                            scanf("%d", &year);
                            printf("수령월을 입력해주세요: \n");
                            scanf("%d", &month);
                            printf("수령일을 입력해주세요: \n");
                            scanf("%d", &day);
                            if(year >= 2023 && year <= 2100 && month > 0 && month < 13 && day > 0 && day < 32) {
                                printf("구매하신 케이크는 %s이며 가격은 %d원입니다.\n", basket, price);
                                printf("수령일은 %d년 %d월 %d일 입니다.\n", year, month, day);
                                printf("구매해주셔서 감사합니다!\n");

                                sprintf(sell_msg, "구매하신 케이크는 %s/ 수령일은 %d년 %d월 %d일 / 금액은 %d원\n", basket, year, month, day, price);
   
                                write(clnt_sock, sell_msg, sizeof(sell_msg));

                                memset(basket, 0 , sizeof(basket));
                                memset(sell_msg, 0, sizeof(sell_msg));
                                price = 0; check_sum = 0; year = 0, month = 0, day = 0;
                                visit++; 
                                sleep(5); 
                                system("clear");
                                break;
                            }
                            else {
                                printf("잘못된 입력입니다.\n\n");
                                sleep(2);

                                system("clear");
                                break;
                            }
                        }        
                        else {
                            printf("메뉴로 돌아갑니다.\n\n");
                            sleep(1);

                            system("clear");
                            break;
                        }
                    }
                case 'X':
                case 'x':
                    system("clear");
                    printf("종료하기를 누르셨습니다.\n");
                    printf("이용해 주셔서 감사합니다. 안녕히 가세요.\n");
                    memset(basket, 0 , sizeof(basket)); 
                    price = 0; check_sum = 0; year = 0, month = 0, day = 0;
                    visit++; 
                    sleep(2); 
                    system("clear");
                    break;
                    // 터미널 비움, 메시지 출력해 주고 모든 변수와 basket 배열 초기화 및 첫 방문 변수 활성화, 읽을 수 있게 기다렸다가 터미널 비움
                default:
                    system("clear");
                    printf("잘못된 입력입니다. 다시 입력해 주세요.\n");
                    // 잘못된 입력은 받지 않음
            }
        }
    }
    close(clnt_sock); // 클라이언트 소켓 닫기

    return 0; // 종료
}

// 에러 메시지 함수
void error_msg(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
} // fputs(): 메시지를 출력, fputc(): 메시지 행 바꿈, exit(): 종료