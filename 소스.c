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
void borrow();   // ���� ���� �Լ�
void return1();   // ���� �ݳ� �Լ�
void list();    // ���� ��� ��� �Լ�
void searchmenu();   // ���� �˻� �޴� �Լ�
void searchname(); // ���������� �˻�
void searchauth(); // ���ڷ� �˻�

typedef struct _book {
    char name[BOOK_NAME_SIZE]; // å ����
    char auth[BOOK_AUTH_SIZE]; // å ����
    char publ[BOOK_PUBL_SIZE]; // å ���ǻ�
    int borrow2;   // ���� ���°� �ƴϸ� 0, ����� �����̸� 1
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

FILE* read, * write;    //���� �ð��� ���� 

struct timewrite {      //���νð��� ���� 
    char* sf;
    int y, mon, day;
    int h, m, s;
}userlist[2];

struct studytime {      //�ð��� ���� ����ü 
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
int sp = 0;             //1�϶� start 
int i = 0;
int num = 0;
int start = 0;
char filename[30];

typedef struct Library {
    char m_name[20];
    char seat[20];      //�¼���Ȳ(O, X�� ǥ���ϱ� ���Ͽ� ���ڿ��� ����)
    int s_count;        //�¼���
}Library;

int pknulibrary, personnel, s_num[3];   //������ ����, �����, �¼�����
int i;
int pknuscreen;
Library mv[2] = { {"�߾ӵ�����", "OOOOOOOOOO", 0}, {"û���", "OOOOOOOOOO", 0} };   //�ʱ� ����

void s_count();
void m_list();
void s_list();
void s_set();
void m_reservation();
void page6();

void load(char* name);  //������ ������ �ҷ���. 
void save();            //������ 
void exitcatch(void);   //������ 
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
    puts("                                           < ȸ������ > \n");
    puts("");
    puts("                                  ���̵�� �й����� �������ּ���");
    puts("                          ���̵�� ��й�ȣ�� ���� �ҹ��ڿ� ���ڸ� �����մϴ�.");
    puts("");
    printf("       ======================================================================================\n");

    join(id, 0);
    join(password, 1);

    puts("");
    puts("");
    puts("");
    printf("                              ++++++++++++++++++++++++++++++++++++++                      \n");
    printf("                              |             ȸ��������             |                     \n");
    printf("                              |           �Ϸ�Ǿ����ϴ�.          |                     \n");
    printf("                              ++++++++++++++++++++++++++++++++++++++                      \n");

    printf("\n\n");
    Sleep(1500);
    system("cls");

    printf("\n\n");
first:
    for (int i = 0; i < 15; i++) {
        printf("                                 %s\n", logo[i]);
    } printf("\n\n\n");

    printf("                                       < �ΰ���б� ������ >            \n");
    printf("                                                       \n");


    do {
        key_code = (login(id, 0) && login(password, 1));

        if (key_code == 1) {
            puts("\n                                        �α��� �Ǿ����ϴ�");
            Sleep(500);
            break;
        }
        else {
            puts("\n                                      �α��ο� �����߽��ϴ�");
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
        printf("         ���ڸ� �Է��ϼ��� : ");
        scanf("%d", &num2);

        if (num2 == 1) { // ���� �ڸ�

            system("cls");
            printf("\n\n");
            printf("           =================================================================================\n");
            printf("            �¼������̷�    \n");
            printf("           =================================================================================\n");

            for (a = 0; a < 20; a++) {

                if (print[a] == NULL || print[a] == 0) {
                    printf("           |  %02d  |              |                                                        |\n", a + 1);
                }

                else {
                    if (printlibrary[a] == 1) {
                        printf("           |  %02d  |  �߾� ������ |   %d�� �¼��� �����ϼ̽��ϴ�.                           |\n", a + 1, print[a]);
                    }

                    else
                        printf("           |  %02d  |    û���    |   %d�� �¼��� �����ϼ̽��ϴ�.                           |\n", a + 1, print[a]);
                }
            }
            printf("           =================================================================================\n");

            Sleep(5000);
        }

        else if (num2 == 2) { // �¼� ���� 
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
                printf("       |     |        |                  1. �� ��  �� �� ��                    |    u   |   |\n");
                printf("       |     |        |                                                        |    d   |   |\n");
                printf("       |     |    K   |                                                        |    y   |   |\n");
                printf("       |     |        |                  2. û �� ��                           |        |   |\n");
                printf("       |     |        |                                                        |        |   |\n");
                printf("       |     |    N   |                                                        |    r   |   |\n");
                printf("       |     |        |                  3. �� ��  �� ��                       |    o   |   |\n");
                printf("       |     |        |                                                        |    o   |   |\n");
                printf("       |     |    U   |                                                        |    m   |   |\n");
                printf("       |     |        |                                                        |        |   |\n");
                printf("       ======================================================================================\n");
                printf("\n");
                printf("                                   ��ȣ�� �����ϼ��� : ");
                scanf("%d", &pknulibrary);

                system("mode con:cols=100 lines=30");
                //�߾� ������
                if (pknulibrary == 1) {
                    mv[pknulibrary - 1].s_count = 0;

                    s_count(); // �¼��� �����ִ��� Ȯ��
                    Sleep(1000);
                    system("cls");
                    m_reservation(); // �¼� �ڸ����
                    printlibrary[b] = 1;
                    b++;
                    system("mode con:cols=100 lines=30");
                }

                //û���
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

                //����
                else if (pknulibrary == 3) {
                    system("mode con:cols=100 lines=30");
                    break;
                }
                else {
                    printf("�߸��� ��ȣ�Դϴ�.\n");
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
                printf("���� ���⿡ �����߽��ϴ�.\n");
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
                printf("        ��---------------------------------------------------------------------------------��\n");
                printf("        ��  .                                                                          .  ��\n");
                printf("        ��                      ------------------------------------                      ��\n");
                printf("        ��                     |           1. [��    ��]            |                     ��\n");
                printf("        ��                     |           2. [��    ��]            |                     ��\n");
                printf("        ��                     |           3. [�������]            |                     ��\n");
                printf("        ��                     |           4. [��    ��]            |                     ��\n");
                printf("        ��                     |           5. [��    ��]            |                     ��\n");
                printf("        ��                      ------------------------------------                      ��\n");
                printf("        ��                                                                                ��\n");
                printf("        ��                                                                                ��\n");
                printf("        ��                                                                                ��\n");
                printf("        ��                                                                                ��\n");
                printf("        ��  .                                                                         .   ��\n");
                printf("        ��                                                                                ��\n");
                printf("        ��---------------------------------------------------------------------------------��\n");
                printf("          ��ȣ �Է� : ");


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
                    printf("\n\n          ���� ���� ���α׷��� �����մϴ�.\n\n");
                    Sleep(1000);
                    system("cls");

                    break;
                }

                else
                {
                    printf("          �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n\n");
                    printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
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
            char study[10];//�Է¹��� ���� 
            timelist[0].stop = 0;
            puts("");
            printf("        ��---------------------------------------------------------------------------------��\n");
            printf("        ��                         username(�����̸�)�� �Է����ּ���.                     ��\n");
            printf("        ��---------------------------------------------------------------------------------��\n");
            printf("                                               ");
            scanf("%s", user);
            sprintf(filename, "%s.txt", user);
            puts("");
            //  load(&user);
            printf("                                         < command ��� > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");

            while (1) {
                printf("                                               ");
                scanf("%s", command);

                if (GetKeyState(VK_F2) < 0 || strstr(command, "1")) {
                    if (sp == 0) {
                        atexit(exitcatch);//����ڰ� �����ϸ� ���� ���¸� �����Ѵ�.
                        sp++;
                    }
                    system("cls");
                    printf("\n                                         < command ��� > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");
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
                        printf("\n                                         < command ��� > \n+--------------------------------------------------------------------------------------------------+\n                           1. start    2. stop    3. show    4. esc    \n+--------------------------------------------------------------------------------------------------+\n");
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

        else if (num2 == 5) { // ����
            system("cls");
            int myinfo;
            char input;

            printf("\n");
            printf("\n");
            printf("        ��---------------------------------------------------------------------------------��\n");
            printf("        ��  .                                                                          .  ��\n");
            printf("        ��                      ------------------------------------                      ��\n");
            printf("        ��                     |          1. ��й�ȣ ã��          |                     ��\n");
            printf("        ��                     |          2. �� ��  �� ��           |                     ��\n");
            printf("        ��                      ------------------------------------                      ��\n");
            printf("        ��                                                                                ��\n");
            printf("        ��                                                                                ��\n");
            printf("        ��                                                                                ��\n");
            printf("        ��                                                                                ��\n");
            printf("        ��  .                                                                         .   ��\n");
            printf("        ��                                                                                ��\n");
            printf("        ��---------------------------------------------------------------------------------��\n");
            printf("         ��ȣ�� �����ϼ��� : ");
            scanf_s("%d", &myinfo);

        JUMP:
            if (myinfo == 1) {
                system("cls");
                printf("\n");
                printf("\n");
                printf("\n");
                printf("\n");
                printf("       ======================================================================================\n");
                printf("                     �й� Ȯ�� : ");
                scanf("%s", &hb);
                printf("       ======================================================================================\n");
                puts("");

                if (!strcmp(hb, id)) {
                    printf("                     ��й�ȣ�� %s�Դϴ�.\n", password);
                }
                else {
                    printf("                     �й��� �ùٸ��� �ʽ��ϴ�.");
                    Sleep(1000);
                    goto JUMP;
                }
            }
            else if (myinfo == 2 || myinfo == 3) {

            }
            else {
                printf(" �߸��� ��ȣ�Դϴ�.\n");
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
            printf("       |     |        |                  ���α׷��� �����մϴ�.                |        |   |\n");
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

        else  printf("                                   �߸��� ��ȣ�Դϴ�. �ٽ� �Է����ּ���\n");
        Sleep(1000);
        goto START;

    } while (num2 >= 1 && num2 <= 6);
    //}

    return 0;
}


//=================================
// Ŀ�� �����
void cursorDisplay(const char* _Mode) {

    printf(CSI"?25l");
}
// ���� ȭ��
void page2(int num2) {

    printf("\n");
    printf("         ._________________________________________________________________________________.\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              1) ���� �ڸ�               |              2) �¼�����              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              3) ����/�ݳ�               |              4) ���α��              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |              5) ȸ������                |              6) ȯ�漳��              |\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |                                       |\n");
    printf("         |.........................................|.......................................|\n");
    printf("         |                                         |                                       |\n");
    printf("         |                                         |            +---+---+---+---+          |\n");
    printf("         |              7) ���α׷� ����           |            | P | K | N | U |          |\n");
    printf("         |                                         |            +---+---+---+---+          |\n");
    printf("         |.�ߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣ�|�ߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣߣ�.|\n");
    printf("\n");
   

}

//=================================

/*
void libraryname(int pknulibrary) {
    if (pknulibrary == 1) {
        printf("�߾� ������");
    }
    if (pknulibrary == 2) {
        printf("û���");
    }
}
void myseat(int pknulibrary) {

    puts("");
    puts("");
    printf("       ======================================================================================\n");
    printf("         ���� �ڸ� \n");
    printf("       ======================================================================================\n");

    for (int i = 0; i <= 10; i++) {
        printf("       |  %d   |  %s        : %d \n", i, libraryname(pknulibrary),i);
    }
}*/

//=================================
// �¼����� (2) ȭ�� 
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
    printf("       |     |        |                  1. �� ��  �� �� ��                    |    u   |   |\n");
    printf("       |     |        |                                                        |    d   |   |\n");
    printf("       |     |    K   |                                                        |    y   |   |\n");
    printf("       |     |        |                  2. û �� ��                           |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |    N   |                                                        |    r   |   |\n");
    printf("       |     |        |                  3. �� ��  �� ��                       |    o   |   |\n");
    printf("       |     |        |                                                        |    o   |   |\n");
    printf("       |     |    U   |                                                        |    m   |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       ======================================================================================\n");
    printf("\n");
    printf("                                   ��ȣ�� �����ϼ��� : ");
    scanf("%d", &pknulibrary);

    //�߾� ������
    if (pknulibrary == 1)
    {
        mv[pknulibrary - 1].s_count = 0;

        s_count(); // �¼��� �����ִ��� Ȯ��
        Sleep(500);
        system("cls");


    }

    //û���
    else if (pknulibrary == 2)
    {
        mv[pknulibrary - 1].s_count = 0;
        s_count(mv, pknulibrary - 1);
        Sleep(500);
        system("cls");
    }

    //����
    else if (pknulibrary == 3) {

        system("mode con:cols=100 lines=30");
        page2(num2);
        printf("         ���ڸ� �Է��ϼ��� : ");
        scanf("%d", &pknulibrary);

    }
    else {

        printf(" �߸��� ��ȣ�Դϴ�.\n");
    }

    printf("\n");

}

// �¼����� (2) �Լ� 
void s_count() {
    for (i = 0; i < 20; i++)
    {
        if (mv[pknulibrary - 1].seat[i] == 'O')
        {
            mv[pknulibrary - 1].s_count++;    //�¼��� O���� ǥ�� ������ O�� ���� ī��Ʈ
        }
    }
}
void m_reservation() {
    //���� ����

    if (mv[pknulibrary - 1].s_count > 0) {

        personnel = 1;

        if (personnel <= mv[pknulibrary - 1].s_count)
        {
            for (;;)
            {
                s_list();
                s_set(); // �¼� �Է��ϴ� �Լ�
                puts("");
                printf("                                       ����Ǿ����ϴ�.");
                Sleep(1000);
                system("cls");
                break;
            }
        }


        //
        else if (personnel > mv[pknulibrary].s_count) {

            printf(" �¼��� �����մϴ�.\n");
            printf(" ���� �¼� %d\n", mv[0].s_count);

            m_list();
        }
    }

    //�ڸ��� ���� �� 
    else {
        printf("                                      �ش� �ڸ��� �̹� ����� �ڸ��Դϴ�.\n");
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
    printf("                                ��           ��            ��           Ȳ                     \n");
    printf("       ======================================================================================\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |              �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�          |        |   |\n");
    printf("       |     |        |              |                              |          |        |   |\n");
    printf("       |     |        |              |     1 2 3 4 5 6 7 8 9 10     |          |        |   |\n");
    printf("       |     |        |              |     ");
    for (i = 0; i < 10; i++) {
        printf("%c ", mv[pknulibrary - 1].seat[i]);
    }

    printf("     |          |        |   | \n");
    printf("       |     |        |              |                              |          |        |   |\n");
    printf("       |     |        |              �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�          |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       |     |        |                                                        |        |   |\n");
    printf("       ======================================================================================\n");
    printf("\n");

}
void s_set() {

    for (i = 0; i < personnel; i++) {
        printf("                                       �¼� ���� : ", i + 1);
        scanf("%d", &s_num[i]);

        if (1 > s_num[i] || s_num[i] > 10) {
            printf("                                      ���� �ڸ��Դϴ�.\n");
            i--;
        }

        else if (mv[pknulibrary - 1].seat[s_num[i] - 1] == 'X') {
            printf("                                  �ش� �ڸ��� �̹� ����� �ڸ��Դϴ�.\n");
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
// ����/�ݳ� (3) �Լ�
void join(char a[], int i) {

    puts("");
    if (i == 0) {
        printf("\n       -> ���̵� �Է��ϼ��� : ");
        scanf("%s", a);
    }

    if (i == 1) {
        printf("       -> ��й�ȣ�� �Է��ϼ��� : ");
        scanf("%s", a);
    }

    char* p = a;

out:

    while (strlen(a) > limit) {
        puts("          ���ڼ��� �ʰ��߽��ϴ�");
        scanf("%s", a);
    }

    //do
    //{
    for (int i = 0; i <= limit; i++) {
        if (islower(*(p + i)) == 0) {
            if (isdigit(*(p + i)) == 0) {
                if (*(p + i) != NULL) {
                    printf("%s\n", a);
                    puts("          �߸��� ���ڰ� �ԷµǾ� �ֽ��ϴ�.");
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
        printf("                                    ���̵� : ");
        scanf("%s", arr);
    }

    if (i == 1) {
        printf("\n                                    ��й�ȣ : ");
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

    printf("\n\n          ������ ������ �̸��� �Է����ּ��� : ");
    gets(bookname);

    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(bookname, booklist[i].name))
        {
            if (booklist[i].borrow2 == 0)
            {
                booklist[i].borrow2 = 1;
                printf("          ����Ǿ����ϴ�.\n\n");
                printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
                _getch();
                return;
            }
            else
            {
                printf("          �� ������ �̹� ����Ǿ����ϴ�.\n\n");
                printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
                _getch();
                return;
            }
        }
    }

    printf("          �� �̸��� ���� ������ �����ϴ�.\n\n");

    printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
    _getch();
}
void return1()
{
    char bookname[BOOK_NAME_SIZE] = { 0, };

    printf("\n\n          �ݳ��� ������ �̸��� �Է����ּ��� : ");
    gets(bookname);

    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(bookname, booklist[i].name))
        {
            if (booklist[i].borrow2 == 1)
            {
                booklist[i].borrow2 = 0;
                printf("          �ݳ��Ǿ����ϴ�.\n\n");
                printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
                _getch();
                return;
            }
            else
            {
                printf("          �� ������ ���� ���°� �ƴմϴ�.\n\n");
                printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
                _getch();
                return;
            }
        }
    }

    printf("          �� �̸��� ���� ������ �����ϴ�.\n\n");
    printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
    _getch();
}
void list()
{
    printf("\n\n");
    if (!bookindex)
    {
        printf("          ���� ����� �����\n\n");
        printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
        _getch();
        return;
    }
    for (i = 0; i < bookindex; i++)
    {
        printf("                                   =========================\n");
        printf("                                   ������ : %s\n", booklist[i].name);
        printf("                                   ��  �� : %s\n", booklist[i].auth);
        printf("                                   ���ǻ� : %s\n", booklist[i].publ);
        printf("                                   ������� : %s\n", (booklist[i].borrow2 == 1) ? "���� ���� å" : "���� ������ å");
    }
    printf("                                   =========================\n\n");



    printf("\n                                  ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
    _getch();
}
void searchmenu()
{
    char input[20] = { 0, };

    printf("\n\n          �˻��� ����� ������  \n\n          1.[������˻�]\n          2.[���ڰ˻�]  \n\n          -> ");
    gets(input);

    system("cls");
    printf("\n");
    printf("        ��---------------------------------------------------------------------------------��\n");
    printf("        ��  .                                                                          .  ��\n");
    printf("        ��                      ------------------------------------                      ��\n");
    printf("        ��                     |           1. [��    ��]            |                     ��\n");
    printf("        ��                     |           2. [��    ��]            |                     ��\n");
    printf("        ��                     |           3. [�������]            |                     ��\n");
    printf("        ��                     |           4. [��    ��]            |                     ��\n");
    printf("        ��                     |           5. [��    ��]            |                     ��\n");
    printf("        ��                      ------------------------------------                      ��\n");
    printf("        ��                                                                                ��\n");
    printf("        ��                                                                                ��\n");
    printf("        ��                                                                                ��\n");
    printf("        ��                                                                                ��\n");
    printf("        ��  .                                                                         .   ��\n");
    printf("        ��                                                                                ��\n");
    printf("        ��---------------------------------------------------------------------------------��\n");

    if (!strcmp(input, "1"))
        searchname();
    else if (!strcmp(input, "2"))
        searchauth();
    else
    {
        printf("\n          �߸��� �Է��Դϴ�.\n\n");
        printf("          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
        _getch();
    }
}
void searchname()
{
    int namelength;    // �˻��� å �̸��� ����
    int samecnt;       // å �̸� �� ���ھ� ��, ������ 1�� ����
    int searchcnt = 0; // �� �˻��� ���� ����
    char bookname[BOOK_NAME_SIZE] = { 0, };

    printf("\n          �������� �Է��ϼ��� : ");
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
            printf("          ������ : %s\n", booklist[i].name);
            printf("          ��  �� : %s\n", booklist[i].auth);
            printf("          ���ǻ� : %s\n", booklist[i].publ);
            printf("          ������� : %s\n", (booklist[i].borrow2 == 1) ? "���� ���� å" : "���� ������ å");
            searchcnt++;
        }
    }
    if (searchcnt)
        printf("          =======================\n\n");
    else
        printf("          �˻��� ������ ã�� ���߽��ϴ�.\n\n");

    printf("\          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
    _getch();
}
void searchauth()
{
    int searchcnt = 0;
    char bookauth[BOOK_AUTH_SIZE] = { 0, };

    printf("\n          ������ �̸��� �Է��ϼ��� : ");
    gets(bookauth);


    for (i = 0; i < bookindex; i++)
    {
        if (!strcmp(booklist[i].auth, bookauth))
        {
            printf("          =======================\n");
            printf("          ������ : %s\n", booklist[i].name);
            printf("          ��  �� : %s\n", booklist[i].auth);
            printf("          ���ǻ� : %s\n", booklist[i].publ);
            printf("          ������� : %s\n", (booklist[i].borrow2 == 1) ? "���� ���� å" : "���� ������ å");
            searchcnt++;
        }
    }

    if (searchcnt)
        printf("          =======================\n\n");
    else
        printf("          �˻��� ������ ������ ã�� ���߽��ϴ�.\n\n");

    printf("\n          ����Ϸ��� �ƹ� Ű�� �Է��ϼ���...");
    _getch();
}
//=================================

//=================================
// ���α�� (4) �Լ�
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
    printf("                         %d�� ", userlist[0].y);
    printf("%d�� ", userlist[0].mon);
    printf("%d�� ", userlist[0].day);
    printf("%d�� ", userlist[0].h);
    printf("%d�� ", userlist[0].m);
    printf("%d�ʿ� ���θ� �����մϴ�.\n", userlist[0].s);
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
        if (num < result) {//�׳� ������������ ���
            system("shutdown -a");
            return 0;
        }
        system("shutdown -a");
        system("shutdown -s -t 1");
    }
}
void log() { //���νð��� ������. 
    totalstudy();
    write = fopen("studytime.txt", "a+");
    fprintf(write, "%d��%d��%d�� ~ ", userlist[i].y, userlist[i].mon, userlist[i].day);
    fprintf(write, "%d��%d��%d�� = ", userlist[1].y, userlist[1].mon, userlist[1].day);
    fprintf(write, "��%d�ð� %d�� %d�ʸ� �����ϼ̽��ϴ�.\n", timelist[0].h, timelist[0].m, timelist[0].s);//h
    fclose(write);
}
void timeshow() { //������ �ð��� ������. 
    totalstudy();
    puts("");  puts("");  puts("");
    printf("        ---------------------------------------------------------------------------------\n");
    printf("        ---------------------------------------------------------------------------------\n");
    puts("");
    printf("                                   %d�ð� %d�� %d�� �����߽��ϴ�.                        \n", timelist[0].h, timelist[0].m, timelist[0].s);
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
    printf("                                        �� �Ͻ� �������Դϴ�.��                       \n");
    printf("                                   �ƹ�Ű�� �Է��ϸ� ���۵˴ϴ�.                         \n");
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
    //���ݽð�-ó���ð��ϸ� -�ð��� ��µǹǷ� �����ϰ� ���� ������Ѵ�.
    int time1 = userlist[1].h * 3600 + userlist[1].m * 60 + userlist[1].s;
    int time2 = userlist[i].h * 3600 + userlist[i].m * 60 + userlist[i].s;
    result = time1 - time2 + timelist[0].stop;
    int temp = result % 3600;
    timelist[i].h = result / 3600;//0�� ó���ð� 
    timelist[i].m = temp / 60;
    timelist[i].s = result % 60;
}
void exitcatch(void) {
    //save=1;
    save();
}
//=================================


// ȯ�漳�� (6) �Լ�
void page6() {

    system("cls");
    printf("\n");
    printf("\n");
    printf("        ��---------------------------------------------------------------------------------��\n");
    printf("        ��  .                                                                           .  ��\n");
    printf("        ��                      ------------------------------------                       ��\n");
    printf("        ��                     |          1. �� ũ  �� ��           |                      ��\n");
    printf("        ��                     |          2. ȭ �� Ʈ  �� ��        |                      ��\n");
    printf("        ��                     |          3. �� ��  �� ��           |                      ��\n");
    printf("        ��                      ------------------------------------                       ��\n");
    printf("        ��                                                                                 ��\n");
    printf("        ��                                                                                 ��\n");
    printf("        ��                                                                                 ��\n");
    printf("        ��                                                                                 ��\n");
    printf("        ��  .                                                                          .   ��\n");
    printf("        ��                                                                                 ��\n");
    printf("        ��---------------------------------------------------------------------------------��\n");
    printf("          ��ȣ�� �����ϼ��� : ");
    scanf_s("%d", &pknuscreen);
    printf("\n");

    //��ũ���
    if (pknuscreen == 1) {
        system("color 07");
        Sleep(1000);
        //mainscreen(num2);
    }

    //ȭ��Ʈ���
    else if (pknuscreen == 2) {
        system("color 70");
        Sleep(1000);
        //mainscreen(num2);
    }

    //����
    else if (pknuscreen == 3) {

        //mainscreen(num2);
    }
}
