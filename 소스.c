#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define BOOK_NAME_SIZE 50
#define BOOK_AUTH_SIZE 30
#define BOOK_PUBL_SIZE 30
#define limit 9
#define ESC "\x1b"       // ESCape
#define CSI "\x1b["      // Control Sequence Introducer


char id[limit + 1] = "";
char password[limit + 1] = "";
char hb[limit + 1] = "";

void cursorDisplay();
void borrow();   // 도서 대출 함수
void return1();   // 도서 반납 함수
void list();    // 도서 목록 출력 함수
void searchmenu();   // 도서 검색 메뉴 함수
void searchname(); // 도서명으로 검색
void searchauth(); // 저자로 검색

typedef struct _book {
    char name[BOOK_NAME_SIZE]; // 책 제목
    char auth[BOOK_AUTH_SIZE]; // 책 저자
    char publ[BOOK_PUBL_SIZE]; // 책 출판사
    int borrow2;   // 대출 상태가 아니면 0, 대출된 상태이면 1
}Book;

FILE* fp;
Book booklist[100];
int bookindex = 0;
int i, j;

void join(char a[], int i);
int login(char a[], int i);
void page2();
void mainscreen(int num2);

FILE* fp;
Book booklist[100];
int i, j;
int a, b = 0;

FILE* read, * write;    //현재 시간을 저장 

struct timewrite {      //공부시간을 저장 
    char* sf;
    int y, mon, day;
    int h, m, s;
}userlist[2];

struct studytime {      //시간을 위한 구조체 
    int h, m, s;
    int stop;
}timelist[1];

struct tm* now;
struct tm* sec;
struct tm* mon;
struct tm* min;
struct tm* mday;
struct tm* mhour;
time_t now_t;

int result;
int sp = 0;             //1일때 start 
int i = 0;
int num = 0;
int start = 0;
char filename[30];

typedef struct Library {
    char m_name[20];
    char seat[20];      //좌석현황(O, X로 표시하기 위하여 문자열로 지정)
    int s_count;        //좌석수
}Library;

int pknulibrary, personnel, s_num[3];   //도서관 선택, 사람수, 좌석선택
int i;
int pknuscreen;
Library mv[2] = { {"중앙도서관", "OOOOOOOOOO", 0}, {"청운관", "OOOOOOOOOO", 0} };   //초기 세팅

void s_count();
void m_list();
void s_list();
void s_set();
void m_reservation();
void page6();

void load(char* name);  //저장한 내용을 불러옴. 
void save();            //저장함 
void exitcatch(void);   //저장함 
void starttime();
void log();
void stop();
void totalstudy();
void timeshow();
void libraryname(int pknulibrary);
void myseaat();

int num, num2 = 0;
int print[20] = { 0 };
int printlibrary[20] = { 0, };
int printnum = 0;

int main(void) {
    cursorDisplay();
    system("mode con:cols=100 lines=30");
    system("color 70");

    int num = 0;
    int num2 = 0;
    char logo[15][32] = {
 "               .              ",
 "               |              ",
 "              7i .            ",
 "      ,8y ,LPOQ.BBb: : c.     ",
 "     Q@ : oddSCd.RBB@R  Rk    ",
 "    B@  dpStttO. ,B@B@B  Qd   ",
 "   E@J IP2kt2PO.  @BQB@@ iQy  ",
 "   BB  dCUt2ooI.   o@B@B@ Zb  ",
 "   B@.dStk9.   t@B@BQ@@B. .8d ",
 "   UB9 7dt2SI  JB@BQB@Bp  L@i ",
 "    RB : jdSpd  jBB@B@BQ .@y  ",
 "     yBU : dEQ7 jBBB@BL iZ :  ",
 "        Jo:U9 C@Bbr : i       ",
 "               ib.            ",
 "               |              "
    };

    char id[limit + 1] = "";
    char password[limit + 1] = "";
    int key_code;
    int erase = 0;

    puts("");
    puts("");
    printf("       ======================================================================================\n");
    puts("                                           < 회원가입 > \n");
    puts("");
    puts("                                  아이디는 학번으로 설정해주세요");
    puts("                          아이디와 비밀번호는 영어 소문자와 숫자만 가능합니다.");
    puts("");
    printf("       ======================================================================================\n");

    join(id, 0);
    join(password, 1);

    puts("");
    puts("");
    puts("");
    printf("                              ++++++++++++++++++++++++++++++++++++++                      \n");
    printf("                              |             회원가입이             |                     \n");
    printf("                              |           완료되었습니다.          |                     \n");
    printf("                              ++++++++++++++++++++++++++++++++++++++                      \n");

    printf("\n\n");
    Sleep(1500);
    system("cls");

    printf("\n\n");
first:
    for (int i = 0; i < 15; i++) {
        printf("                                 %s\n", logo[i]);
    } printf("\n\n\n");

    printf("                                       < 부경대학교 도서관 >            \n");
    printf("                                                       \n");


    do {
        key_code = (login(id, 0) && login(password, 1));

        if (key_code == 1) {
            puts("\n                                        로그인 되었습니다");
            Sleep(500);
            break;
        }
        else {
            puts("\n                                      로그인에 실패했습니다");
            Sleep(1000);
            system("cls");
            puts("\n");
            goto first;
        }
    } while (key_code != 1);


    Sleep(1000);

    do {
        system("mode con:cols=100 lines=30");
    START:
        system("cls");
        page2(num2);
        printf("         숫자를 입력하세요 : ");
        scanf("%d", &num2);

        if (num2 == 1) { // 나의 자리

            system("cls");
            printf("\n\n");
            printf("           =================================================================================\n");
            printf("            좌석예약이력    \n");
            printf("           =================================================================================\n");

            for (a = 0; a < 20; a++) {

                if (print[a] == NULL || print[a] == 0) {
                    printf("           |  %02d  |              |                                                        |\n", a + 1);
                }

                else {
                    if (printlibrary[a] == 1) {
                        printf("           |  %02d  |  중앙 도서관 |   %d번 좌석을 예약하셨습니다.                           |\n", a + 1, print[a]);
                    }

                    else
                        printf("           |  %02d  |    청운관    |   %d번 좌석을 예약하셨습니다.                           |\n", a + 1, print[a]);
                }
            }
            printf("           =================================================================================\n");

            Sleep(5000);
        }

        else if (num2 == 2) { // 좌석 선택 
            for (;;) {
                system("cls");
                printf("\n");
                printf("\n");
                printf("           '||''|.'||'  |''|.   '|'||'  '|'  '||'      ||'||                                 \n");
                printf("            ||   |||| .'   |'|   | ||    |    ||      ... || ...... .. ....  ... ..... ...   \n");
                printf("            ||...|'||'|.   | '|. | ||    |    ||       || ||'  ||||' ''' .||  ||' ''|.  |    \n");
                printf("            ||     ||  ||  |   ||| ||    |    ||       || ||    |||   .|' ||  ||    '|.|     \n");
                printf("           .||.   .||.  ||.|.   '|  '|..'    .||.....|.||.'|...'.||.  '|..'|'.||.    '|      \n");
                printf("                                                                                  .. |       \n");
                printf("                                                                                   ''        \n");
                printf("       ======================================================================================\n");
                printf("\n");
                printf("       ======================================================================================\n");
                printf("       |     |        |                                                        |        |   |\n");
                printf("       |     |        |                                                        |    s   |   |\n");
                printf("       |     |    P   |                                                        |    t   |   |\n");
                printf("       |     |        |                  1. 중 앙  도 서 관                    |    u   |   |\n");
                printf("       |     |        |                                                        |    d   |   |\n");
                printf("       |     |    K   |                                                        |    y   |   |\n");
                printf("       |     |        |                  2. 청 운 관                           |        |   |\n");
                printf("       |     |        |                                                        |        |   |\n");
                printf("       |     |    N   |                                                        |    r   |   |\n");
                printf("       |     |        |                  3. 뒤 로  가 기                       |    o   |   |\n");
                printf("       |     |        |                                                        |    o   |   |\n");
                printf("       |     |    U   |                                                        |    m   |   |\n");
                printf("       |     |        |                                                        |        |   |\n");
                printf("       ======================================================================================\n");
                printf("\n");
                printf("                                   번호를 선택하세요 : ");
                scanf("%d", &pknulibrary);

                system("mode con:cols=100 lines=30");
                //중앙 도서관
                if (pknulibrary == 1) {
                    mv[pknulibrary - 1].s_count = 0;

                    s_count(); // 좌석이 남아있는지 확인
                    Sleep(1000);
                    system("cls");
                    m_reservation(); // 좌석 자리잡기
                    printlibrary[b] = 1;
                    b++;
                    system("mode con:cols=100 lines=30");
                }

                //청운관
                else if (pknulibrary == 2) {
                    mv[pknulibrary - 1].s_count = 0;
                    s_count(mv, pknulibrary - 1);
                    Sleep(1000);
                    system("cls");
                    m_reservation();
                    printlibrary[b] = 2;
                    b++;
                    system("mode con:cols=100 lines=30");
                }

                //종료
                else if (pknulibrary == 3) {
                    system("mode con:cols=100 lines=30");
                    break;
                }
                else {
                    printf("잘못된 번호입니다.\n");
                }
                // m_list();

            }
        }

        else if (num2 == 3) {
            system("cls");
            int i = 0;
            char fpname[BOOK_NAME_SIZE];
            char fpauth[BOOK_AUTH_SIZE];
            char fppubl[BOOK_PUBL_SIZE];
            char input[10] = { 0, };

            fp = fopen("booklist.txt", "a+");
            if (fp == NULL) {
                printf("파일 열기에 실패했습니다.\n");
                return 1;
            }

            while (!feof(fp)) {
                fscanf(fp, "%[^,], %[^,], %[^\n]", booklist[i].name, booklist[i].auth, booklist[i].publ);
                fgetc(fp);
                booklist[i].borrow2 = 0;
                bookindex++;
                i++;
            }


            erase = getchar();

            while (1) {
                system("cls");
                printf("\n");
                printf("        ┌---------------------------------------------------------------------------------┐\n");
                printf("        ㅣ  .                                                                          .  ㅣ\n");
                printf("        ㅣ                      ------------------------------------                      ㅣ\n");
                printf("        ㅣ                     |           1. [대    출]            |                     ㅣ\n");
                printf("        ㅣ                     |           2. [반    납]            |                     ㅣ\n");
                printf("        ㅣ                     |           3. [도서목록]            |                     ㅣ\n");
                printf("        ㅣ                     |           4. [검    색]            |                     ㅣ\n");
                printf("        ㅣ                     |           5. [종    료]            |                     ㅣ\n");
                printf("        ㅣ                      ------------------------------------                      ㅣ\n");
                printf("        ㅣ                                                                                ㅣ\n");
                printf("        ㅣ                                                                                ㅣ\n");
                printf("        ㅣ                                                                                ㅣ\n");
                printf("        ㅣ                                                                                ㅣ\n");
                printf("        ㅣ  .                                                                         .   ㅣ\n");
                printf("        ㅣ                                                                                ㅣ\n");
                printf("        └---------------------------------------------------------------------------------┘\n");
                printf("          번호 입력 : ");


                gets(input);

                if (!strcmp(input, "1"))
                    borrow();
                else if (!strcmp(input, "2"))
                    return1();
                else if (!strcmp(input, "3"))
                    list();
                else if (!strcmp(input, "4"))
                    searchmenu();
                else if (!strcmp(input, "5"))
                {
                    printf("\n\n          도서 관리 프로그램을 종료합니다.\n\n");
                    Sleep(1000);
                    system("cls");

                    break;
                }

                else
                {
                    printf("          잘못된 입력입니다. 다시 입력해주세요.\n\n");
                    printf("\n          계속하려면 아무 키나 입력하세요...");
                    _getch();
                    continue;
                }
            }
            fclose(fp);
        }

        else if (num2 == 4) {
            system("cls");

            HWND time = FindWindow("ConsoleWindowClass", NULL);
            SetWindowPos(time, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            char command[20];
            char user[20];
            char study[10];//입력받을 문자 
            timelist[0].stop = 0;
            puts("");
            printf("        ┌---------------------------------------------------------------------------------┐\n");
            printf("        ㅣ                         username(파일이름)을 입력해주세요.                     ㅣ\n");
            printf("        └---------------------------------------------------------------------------------┘\n");
            printf("                                               ");
            scanf("%s", user);
            sprintf(filename, "%s.txt", user);
            puts("");
            //  load(&user);
            printf("                                         < command 목록 > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");

            while (1) {
                printf("                                               ");
                scanf("%s", command);

                if (GetKeyState(VK_F2) < 0 || strstr(command, "1")) {
                    if (sp == 0) {
                        atexit(exitcatch);//사용자가 종료하면 현재 상태를 저장한다.
                        sp++;
                    }
                    system("cls");
                    printf("\n                                         < command 목록 > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");
                    starttime();
                    start++;
                }

                else if (GetKeyState(VK_F1) < 0 || strstr(command, "3")) {
                    if (start != 0) {

                        timeshow();
                    }
                }
                else if (GetKeyState(VK_F10) < 0 || strstr(command, "2")) {
                    if (start != 0) {
                        system("cls");
                        printf("\n                                         < command 목록 > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");
                        timeshow();
                        stop();
                    }
                }
                else if (GetKeyState(VK_F10) < 0 || strstr(command, "4")) {
                    if (start != 0) {
                        system("cls");
                        break;
                    }
                }
                if (num != 0 && num < result) {
                    num = 0;
                    system("shutdown -a");
                }
            }
        }

        else if (num2 == 5) { // 정보
            system("cls");
            int myinfo;
            char input;

            printf("\n");
            printf("\n");
            printf("        ┌---------------------------------------------------------------------------------┐\n");
            printf("        ㅣ  .                                                                          .  ㅣ\n");
            printf("        ㅣ                      ------------------------------------                      ㅣ\n");
            printf("        ㅣ                     |          1. 비밀번호 찾기          |                     ㅣ\n");
            printf("        ㅣ                     |          2. 뒤 로  가 기           |                     ㅣ\n");
            printf("        ㅣ                      ------------------------------------                      ㅣ\n");
            printf("        ㅣ                                                                                ㅣ\n");
            printf("        ㅣ                                                                                ㅣ\n");
            printf("        ㅣ                                                                                ㅣ\n");
            printf("        ㅣ                                                                                ㅣ\n");
            printf("        ㅣ  .                                                                         .   ㅣ\n");
            printf("        ㅣ                                                                                ㅣ\n");
            printf("        └---------------------------------------------------------------------------------┘\n");
            printf("         번호를 선택하세요 : ");
            scanf_s("%d", &myinfo);

        JUMP:
            if (myinfo == 1) {
                system("cls");
                printf("\n");
                printf("\n");
                printf("\n");
                printf("\n");
                printf("       ======================================================================================\n");
                printf("                     학번 확인 : ");
                scanf("%s", &hb);
                printf("       ======================================================================================\n");
                puts("");

                if (!strcmp(hb, id)) {
                    printf("                     비밀번호는 %s입니다.\n", password);
                }
                else {
                    printf("                     학번이 올바르지 않습니다.");
                    Sleep(1000);
                    goto JUMP;
                }
            }
            else if (myinfo == 2 || myinfo == 3) {

            }
            else {
                printf(" 잘못된 번호입니다.\n");
            }
        }

        else if (num2 == 6) {
            page6();
        }

        else if (num2 == 7) {
            system("cls");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("       ======================================================================================\n");
            printf("              P U K Y O N G     N A T I O N A L    U N I V E R S I T Y     L I B R A R Y     \n");
            printf("       ======================================================================================\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                  프로그램을 종료합니다.                |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       |     |        |                                                        |        |   |\n");
            printf("       ======================================================================================\n");
            printf("              P U K Y O N G     N A T I O N A L    U N I V E R S I T Y     L I B R A R Y   \n");
            printf("       ======================================================================================\n");
            printf("\n");
            printf("           '||''|.'||'  |''|.   '|'||'  '|'  '||'      ||'||                                \n");
            printf("            ||   |||| .'   |'|   | ||    |    ||      ... || ...... .. ....  ... ..... ...  \n");
            printf("            ||...|'||'|.   | '|. | ||    |    ||       || ||'  ||||' ''' .||  ||' ''|.  |  \n");
            printf("            ||     ||  ||  |   ||| ||    |    ||       || ||    |||   .|' ||  ||    '|.|   \n");
            printf("           .||.   .||.  ||.|.   '|  '|..'    .||.....|.||.'|...'.||.  '|..'|'.||.    '|    \n");
            printf("                                                                                  .. |     \n");
            printf("                                                                                   ''      \n");
            Sleep(2000);
            break;
        }

        else  printf("                                   잘못된 번호입니다. 다시 입력해주세요\n");
        Sleep(1000);
        goto START;

    } while (num2 >= 1 && num2 <= 6);
    //}

    return 0;
}


//=================================
// 커서 지우기
void cursorDisplay(const char* _Mode) {

    printf(CSI"?25l");
}
// 메인 화면
void page2(int num2) {

    printf("\n");
    printf("         ._________________________________________________________________________________.\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              1) 나의 자리               |              2) 좌석선택              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              3) 대출/반납               |              4) 공부기록              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              5) 회원정보                |              6) 환경설정              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |            +---+---+---+---+          |\n");
    printf("         |              7) 프로그램 종료           |            | P | K | N | U |          |\n");
    printf("         |                                         |            +---+---+---+---+          |\n");
    printf("         |.＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿|＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿.|\n");
    printf("\n");
   

}

//=================================

/*
void libraryname(int pknulibrary) {
    if (pknulibrary == 1) {
        printf("중앙 도서관");
    }
    if (pknulibrary == 2) {
        printf("청운관");
    }
}
void myseat(int pknulibrary) {

    puts("");
    puts("");
    printf("       ======================================================================================\n");
    printf("         나의 자리 \n");
    printf("       ======================================================================================\n");

    for (int i = 0; i <= 10; i++) {
        printf("       |  %d   |  %s        : %d \n", i, libraryname(pknulibrary),i);
    }
}*/

//=================================
// 좌석선택 (2) 화면 
void m_list() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("           '||''|.'||'  |''|.   '|'||'  '|'  '||'      ||'||                                \n");
    printf("            ||   |||| .'   |'|   | ||    |    ||      ... || ...... .. ....  ... ..... ...  \n");
    printf("            ||...|'||'|.   | '|. | ||    |    ||       || ||'  ||||' ''' .||  ||' ''|.  |  \n");
    printf("            ||     ||  ||  |   ||| ||    |    ||       || ||    |||   .|' ||  ||    '|.|   \n");
    printf("           .||.   .||.  ||.|.   '|  '|..'    .||.....|.||.'|...'.||.  '|..'|'.||.    '|    \n");
    printf("                                                                                  .. |     \n");
    printf("                                                                                   ''      \n");
    printf("       ======================================================================================\n");
    printf("\n");
    printf("       ======================================================================================\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |    s   |   |\n");
    printf("       |     |    P   |                                                        |    t   |   |\n");
    printf("       |     |        |                  1. 중 앙  도 서 관                    |    u   |   |\n");
    printf("       |     |        |                                                        |    d   |   |\n");
    printf("       |     |    K   |                                                        |    y   |   |\n");
    printf("       |     |        |                  2. 청 운 관                           |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |    N   |                                                        |    r   |   |\n");
    printf("       |     |        |                  3. 뒤 로  가 기                       |    o   |   |\n");
    printf("       |     |        |                                                        |    o   |   |\n");
    printf("       |     |    U   |                                                        |    m   |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       ======================================================================================\n");
    printf("\n");
    printf("                                   번호를 선택하세요 : ");
    scanf("%d", &pknulibrary);

    //중앙 도서관
    if (pknulibrary == 1)
    {
        mv[pknulibrary - 1].s_count = 0;

        s_count(); // 좌석이 남아있는지 확인
        Sleep(500);
        system("cls");


    }

    //청운관
    else if (pknulibrary == 2)
    {
        mv[pknulibrary - 1].s_count = 0;
        s_count(mv, pknulibrary - 1);
        Sleep(500);
        system("cls");
    }

    //종료
    else if (pknulibrary == 3) {

        system("mode con:cols=100 lines=30");
        page2(num2);
        printf("         숫자를 입력하세요 : ");
        scanf("%d", &pknulibrary);

    }
    else {

        printf(" 잘못된 번호입니다.\n");
    }

    printf("\n");

}

// 좌석선택 (2) 함수 
void s_count() {
    for (i = 0; i < 20; i++)
    {
        if (mv[pknulibrary - 1].seat[i] == 'O')
        {
            mv[pknulibrary - 1].s_count++;    //좌석을 O으로 표시 했으며 O의 수를 카운트
        }
    }
}
void m_reservation() {
    //예매 가능

    if (mv[pknulibrary - 1].s_count > 0) {

        personnel = 1;

        if (personnel <= mv[pknulibrary - 1].s_count)
        {
            for (;;)
            {
                s_list();
                s_set(); // 좌석 입력하는 함수
                puts("");
                printf("                                       예약되었습니다.");
                Sleep(1000);
                system("cls");
                break;
            }
        }


        //
        else if (personnel > mv[pknulibrary].s_count) {

            printf(" 좌석이 부족합니다.\n");
            printf(" 남은 좌석 %d\n", mv[0].s_count);

            m_list();
        }
    }

    //자리가 없을 때 
    else {
        printf("                                      해당 자리는 이미 예약된 자리입니다.\n");
        system("cls");
        m_list();
    }
}


void s_list() {

    printf("\n");
    printf("           '||''|.'||'  |''|.   '|'||'  '|'  '||'      ||'||                                \n");
    printf("            ||   |||| .'   |'|   | ||    |    ||      ... || ...... .. ....  ... ..... ...  \n");
    printf("            ||...|'||'|.   | '|. | ||    |    ||       || ||'  ||||' ''' .||  ||' ''|.  |  \n");
    printf("            ||     ||  ||  |   ||| ||    |    ||       || ||    |||   .|' ||  ||    '|.|   \n");
    printf("           .||.   .||.  ||.|.   '|  '|..'    .||.....|.||.'|...'.||.  '|..'|'.||.    '|    \n");
    printf("                                                                                  .. |     \n");
    printf("                                                                                   ''      \n");
    printf("       ======================================================================================\n");
    printf("                                좌           석            현           황                     \n");
    printf("       ======================================================================================\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |              ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ          |        |   |\n");
    printf("       |     |        |              |                              |          |        |   |\n");
    printf("       |     |        |              |     1 2 3 4 5 6 7 8 9 10     |          |        |   |\n");
    printf("       |     |        |              |     ");
    for (i = 0; i < 10; i++) {
        printf("%c ", mv[pknulibrary - 1].seat[i]);
    }

    printf("     |          |        |   | \n");
    printf("       |     |        |              |                              |          |        |   |\n");
    printf("       |     |        |              ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ          |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       ======================================================================================\n");
    printf("\n");

}
void s_set() {

    for (i = 0; i < personnel; i++) {
        printf("                                       좌석 선택 : ", i + 1);
        scanf("%d", &s_num[i]);

        if (1 > s_num[i] || s_num[i] > 10) {
            printf("                                      없는 자리입니다.\n");
            i--;
        }

        else if (mv[pknulibrary - 1].seat[s_num[i] - 1] == 'X') {
            printf("                                  해당 자리는 이미 예약된 자리입니다.\n");
            i--;
            Sleep(1000);
            system("cls");
            m_list();
            continue;
        }

        else if (mv[pknulibrary - 1].seat[s_num[i] - 1] == 'O') {
            mv[pknulibrary - 1].seat[s_num[i] - 1] = 'X';
            print[printnum] = s_num[i];
            printnum++;
        }
    }

    printf("\n");
}


//=================================

//=================================
// 대출/반납 (3) 함수
void join(char a[], int i) {

    puts("");
    if (i == 0) {
        printf("\n       -> 아이디를 입력하세요 : ");
        scanf("%s", a);
    }

    if (i == 1) {
        printf("       -> 비밀번호를 입력하세요 : ");
        scanf("%s", a);
    }

    char* p = a;

out:

    while (strlen(a) > limit) {
        puts("          글자수를 초과했습니다");
        scanf("%s", a);
    }

    //do
    //{
    for (int i = 0; i <= limit; i++) {
        if (islower(*(p + i)) == 0) {
            if (isdigit(*(p + i)) == 0) {
                if (*(p + i) != NULL) {
                    printf("%s\n", a);
                    puts("          잘못된 문자가 입력되어 있습니다.");
                    scanf("%s", a);
                    goto out;
                    //break;
                }
            }
        }
    }
    //break;
//} while (1);

    puts("");
}
int login(char a[], int i) {
    char arr[limit + 1] = "";

    if (i == 0) {
        printf("                                    아이디 : ");
        scanf("%s", arr);
    }

    if (i == 1) {
        printf("\n                                    비밀번호 : ");
        scanf("%s", arr);
    }

    if (strcmp(a, arr) != 0)
        return 0;
    else
        return 1;

}
void borrow()
{
    char bookname[BOOK_NAME_SIZE] = { 0, };

    printf("\n\n          대출할 도서의 이름을 입력해주세요 : ");
    gets(bookname);

    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(bookname, booklist[i].name))
        {
            if (booklist[i].borrow2 == 0)
            {
                booklist[i].borrow2 = 1;
                printf("          대출되었습니다.\n\n");
                printf("\n          계속하려면 아무 키나 입력하세요...");
                _getch();
                return;
            }
            else
            {
                printf("          위 도서는 이미 대출되었습니다.\n\n");
                printf("\n          계속하려면 아무 키나 입력하세요...");
                _getch();
                return;
            }
        }
    }

    printf("          위 이름을 가진 도서가 없습니다.\n\n");

    printf("\n          계속하려면 아무 키나 입력하세요...");
    _getch();
}
void return1()
{
    char bookname[BOOK_NAME_SIZE] = { 0, };

    printf("\n\n          반납할 도서의 이름을 입력해주세요 : ");
    gets(bookname);

    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(bookname, booklist[i].name))
        {
            if (booklist[i].borrow2 == 1)
            {
                booklist[i].borrow2 = 0;
                printf("          반납되었습니다.\n\n");
                printf("\n          계속하려면 아무 키나 입력하세요...");
                _getch();
                return;
            }
            else
            {
                printf("          위 도서는 대출 상태가 아닙니다.\n\n");
                printf("\n          계속하려면 아무 키나 입력하세요...");
                _getch();
                return;
            }
        }
    }

    printf("          위 이름을 가진 도서가 없습니다.\n\n");
    printf("\n          계속하려면 아무 키나 입력하세요...");
    _getch();
}
void list()
{
    printf("\n\n");
    if (!bookindex)
    {
        printf("          도서 목록이 비었음\n\n");
        printf("\n          계속하려면 아무 키나 입력하세요...");
        _getch();
        return;
    }
    for (i = 0; i < bookindex; i++)
    {
        printf("                                   =========================\n");
        printf("                                   도서명 : %s\n", booklist[i].name);
        printf("                                   저  자 : %s\n", booklist[i].auth);
        printf("                                   출판사 : %s\n", booklist[i].publ);
        printf("                                   대출상태 : %s\n", (booklist[i].borrow2 == 1) ? "대출 중인 책" : "대출 가능한 책");
    }
    printf("                                   =========================\n\n");



    printf("\n                                  계속하려면 아무 키나 입력하세요...");
    _getch();
}
void searchmenu()
{
    char input[20] = { 0, };

    printf("\n\n          검색할 대상을 고르세요  \n\n          1.[도서명검색]\n          2.[저자검색]  \n\n          -> ");
    gets(input);

    system("cls");
    printf("\n");
    printf("        ┌---------------------------------------------------------------------------------┐\n");
    printf("        ㅣ  .                                                                          .  ㅣ\n");
    printf("        ㅣ                      ------------------------------------                      ㅣ\n");
    printf("        ㅣ                     |           1. [대    출]            |                     ㅣ\n");
    printf("        ㅣ                     |           2. [반    납]            |                     ㅣ\n");
    printf("        ㅣ                     |           3. [도서목록]            |                     ㅣ\n");
    printf("        ㅣ                     |           4. [검    색]            |                     ㅣ\n");
    printf("        ㅣ                     |           5. [종    료]            |                     ㅣ\n");
    printf("        ㅣ                      ------------------------------------                      ㅣ\n");
    printf("        ㅣ                                                                                ㅣ\n");
    printf("        ㅣ                                                                                ㅣ\n");
    printf("        ㅣ                                                                                ㅣ\n");
    printf("        ㅣ                                                                                ㅣ\n");
    printf("        ㅣ  .                                                                         .   ㅣ\n");
    printf("        ㅣ                                                                                ㅣ\n");
    printf("        └---------------------------------------------------------------------------------┘\n");

    if (!strcmp(input, "1"))
        searchname();
    else if (!strcmp(input, "2"))
        searchauth();
    else
    {
        printf("\n          잘못된 입력입니다.\n\n");
        printf("          계속하려면 아무 키나 입력하세요...");
        _getch();
    }
}
void searchname()
{
    int namelength;    // 검색할 책 이름의 길이
    int samecnt;       // 책 이름 한 글자씩 비교, 같으면 1씩 증가
    int searchcnt = 0; // 총 검색된 도서 개수
    char bookname[BOOK_NAME_SIZE] = { 0, };

    printf("\n          도서명을 입력하세요 : ");
    gets(bookname);

    namelength = strlen(bookname);

    for (i = 0; i < bookindex; i++)
    {
        samecnt = 0;
        for (j = 0; j < namelength; j++)
        {
            if (bookname[j] == booklist[i].name[j])
                samecnt++;
            else
                break;
        }
        if (samecnt == namelength)
        {
            printf("          =======================\n");
            printf("          도서명 : %s\n", booklist[i].name);
            printf("          저  자 : %s\n", booklist[i].auth);
            printf("          출판사 : %s\n", booklist[i].publ);
            printf("          대출상태 : %s\n", (booklist[i].borrow2 == 1) ? "대출 중인 책" : "대출 가능한 책");
            searchcnt++;
        }
    }
    if (searchcnt)
        printf("          =======================\n\n");
    else
        printf("          검색한 도서를 찾지 못했습니다.\n\n");

    printf("\          계속하려면 아무 키나 입력하세요...");
    _getch();
}
void searchauth()
{
    int searchcnt = 0;
    char bookauth[BOOK_AUTH_SIZE] = { 0, };

    printf("\n          저자의 이름을 입력하세요 : ");
    gets(bookauth);


    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(booklist[i].auth, bookauth))
        {
            printf("          =======================\n");
            printf("          도서명 : %s\n", booklist[i].name);
            printf("          저  자 : %s\n", booklist[i].auth);
            printf("          출판사 : %s\n", booklist[i].publ);
            printf("          대출상태 : %s\n", (booklist[i].borrow2 == 1) ? "대출 중인 책" : "대출 가능한 책");
            searchcnt++;
        }
    }

    if (searchcnt)
        printf("          =======================\n\n");
    else
        printf("          검색한 저자의 도서를 찾지 못했습니다.\n\n");

    printf("\n          계속하려면 아무 키나 입력하세요...");
    _getch();
}
//=================================

//=================================
// 공부기록 (4) 함수
void starttime() {
    //printf("user num = %d\n",user);

    time(&now_t);
    now = localtime(&now_t);
    userlist[i].sf = "start";
    userlist[i].y = now->tm_year + 1900;
    userlist[i].mon = now->tm_mon + 1;
    userlist[i].day = now->tm_mday;
    userlist[i].h = now->tm_hour;
    userlist[i].m = now->tm_min;
    userlist[i].s = now->tm_sec;

    puts("");
    puts("");
    printf("        ---------------------------------------------------------------------------------\n");
    printf("                         %d년 ", userlist[0].y);
    printf("%d월 ", userlist[0].mon);
    printf("%d일 ", userlist[0].day);
    printf("%d시 ", userlist[0].h);
    printf("%d분 ", userlist[0].m);
    printf("%d초에 공부를 시작합니다.\n", userlist[0].s);
    printf("        ---------------------------------------------------------------------------------\n");
    puts("");
    puts("");
}
void save() {
    //if(save==1){
    log();
    write = fopen(filename, "a+");

    fprintf(write, "%s ", userlist[i].sf);//start
    fprintf(write, "%d ", userlist[i].y);//year
    fprintf(write, "%d ", userlist[i].mon);//mon
    fprintf(write, "%d ", userlist[i].day);//day
    fprintf(write, "%d ", userlist[i].h);//h
    fprintf(write, "%d ", userlist[i].m);//m
    fprintf(write, "%d\n", userlist[i].s);//s

    fprintf(write, "%s ", userlist[1].sf);//finish
    fprintf(write, "%d ", userlist[1].y);//year
    fprintf(write, "%d ", userlist[1].mon);//mon
    fprintf(write, "%d ", userlist[1].day);//day
    fprintf(write, "%d ", userlist[1].h);//h
    fprintf(write, "%d ", userlist[1].m);//m	
    fprintf(write, "%d\n", userlist[1].s);//s
    fclose(write);
    if (num != 0) {
        if (num < result) {//그냥 종료했을때를 대비
            system("shutdown -a");
            return 0;
        }
        system("shutdown -a");
        system("shutdown -s -t 1");
    }
}
void log() { //공부시간을 저장함. 
    totalstudy();
    write = fopen("studytime.txt", "a+");
    fprintf(write, "%d년%d월%d일 ~ ", userlist[i].y, userlist[i].mon, userlist[i].day);
    fprintf(write, "%d년%d월%d일 = ", userlist[1].y, userlist[1].mon, userlist[1].day);
    fprintf(write, "총%d시간 %d분 %d초를 공부하셨습니다.\n", timelist[0].h, timelist[0].m, timelist[0].s);//h
    fclose(write);
}
void timeshow() { //공부한 시간을 보여줌. 
    totalstudy();
    puts("");  puts("");  puts("");
    printf("        ---------------------------------------------------------------------------------\n");
    printf("        ---------------------------------------------------------------------------------\n");
    puts("");
    printf("                                   %d시간 %d분 %d초 공부했습니다.                        \n", timelist[0].h, timelist[0].m, timelist[0].s);
    puts("");
    printf("        ---------------------------------------------------------------------------------\n");
    printf("        ---------------------------------------------------------------------------------\n");
}
void stop() {
    //save=1;
    totalstudy();
    timelist[0].stop = result;
    save();
    puts("");
    puts("");
    printf("                                        ※ 일시 정지중입니다.※                       \n");
    printf("                                   아무키나 입력하면 시작됩니다.                         \n");
    puts("");
    getch();
    system("cls");
    starttime();
}
void totalstudy() {
    time(&now_t);
    now = localtime(&now_t);
    userlist[1].sf = "finish";
    userlist[1].y = now->tm_year + 1900;
    userlist[1].mon = now->tm_mon + 1;
    userlist[1].day = now->tm_mday;
    userlist[1].h = now->tm_hour;
    userlist[1].m = now->tm_min;
    userlist[1].s = now->tm_sec;
    //지금시간-처음시간하면 -시간이 출력되므로 간단하게 뭔가 해줘야한다.
    int time1 = userlist[1].h * 3600 + userlist[1].m * 60 + userlist[1].s;
    int time2 = userlist[i].h * 3600 + userlist[i].m * 60 + userlist[i].s;
    result = time1 - time2 + timelist[0].stop;
    int temp = result % 3600;
    timelist[i].h = result / 3600;//0이 처음시간 
    timelist[i].m = temp / 60;
    timelist[i].s = result % 60;
}
void exitcatch(void) {
    //save=1;
    save();
}
//=================================


// 환경설정 (6) 함수
void page6() {

    system("cls");
    printf("\n");
    printf("\n");
    printf("        ┌---------------------------------------------------------------------------------┐\n");
    printf("        ㅣ  .                                                                           .  ㅣ\n");
    printf("        ㅣ                      ------------------------------------                       ㅣ\n");
    printf("        ㅣ                     |          1. 다 크  모 드           |                      ㅣ\n");
    printf("        ㅣ                     |          2. 화 이 트  모 드        |                      ㅣ\n");
    printf("        ㅣ                     |          3. 뒤 로  가 기           |                      ㅣ\n");
    printf("        ㅣ                      ------------------------------------                       ㅣ\n");
    printf("        ㅣ                                                                                 ㅣ\n");
    printf("        ㅣ                                                                                 ㅣ\n");
    printf("        ㅣ                                                                                 ㅣ\n");
    printf("        ㅣ                                                                                 ㅣ\n");
    printf("        ㅣ  .                                                                          .   ㅣ\n");
    printf("        ㅣ                                                                                 ㅣ\n");
    printf("        └---------------------------------------------------------------------------------┘\n");
    printf("          번호를 선택하세요 : ");
    scanf_s("%d", &pknuscreen);
    printf("\n");

    //다크모드
    if (pknuscreen == 1) {
        system("color 07");
        Sleep(1000);
        //mainscreen(num2);
    }

    //화이트모드
    else if (pknuscreen == 2) {
        system("color 70");
        Sleep(1000);
        //mainscreen(num2);
    }

    //종료
    else if (pknuscreen == 3) {

        //mainscreen(num2);
    }
}
