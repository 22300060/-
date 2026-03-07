#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5])
{
    int room; // 랜덤으로 선택된 방 번호를 저장할 변수
    while (1) // 조건을 만족하는 방이 나올 때까지 계속 반복
    {
        room = rand() % 5;     // 0부터 4 사이의 랜덤 숫자를 만듦 (랜덤 함수 사용하는 법을 까먹어서 chatGPT의 도움을 받았습니다)
        if (persons[room] < 2) // 해당 방에 사람이 2명 미만이면
            return room;       // 방 번호를 리턴
    }
}

void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc)
{
    int i, j, k;    
    printf("===========================================\n생활관 호실 배정 결과는 다음과 같습니다.\n===========================================\n");
    printf("남학생 명단 (%d명)\n", mc); // 등록된 남학생 수 출력
    for (i = 0; i < mc; i++)            // 남학생 수만큼 이름, 방번호 출력
    {
        printf("%d. %s [%d호]\n", i + 1, mn[i], mr[i]);
    }
    printf("\n여학생 명단 (%d명)\n", wc); // 등록된 여학생 수를 출력
    for (j = 0; j < wc; j++)              // 여학생 수만큼 이름, 방번호 출력
    {
        printf("%d. %s [%d호]\n", j + 1, wn[j], wr[j]);
    }
    printf("\n호실별 배정 명단\n");
    for (k = 0; k < 5; k++) // 남학생 방(101~105)을 하나씩 확인
    {
        printf("%d호 : ", 101 + k); // 현재 101+k(0~4)방 번호를 출력
        for (i = 0; i < mc; i++)    // 남학생 수를 확인하면서
        {
            if (mr[i] == 101 + k) // 해당 학생의 방 번호가 현재 방과 같다면 그 학생의 이름 출력
                printf("%s ", mn[i]);
        }
        printf("\n");
    }

    for (k = 0; k < 5; k++) // 여학생 방(201~205)을 하나씩 확인.
    {
        printf("%d호 : ", 201 + k); // 현재 101+k(0~4)방 번호를 출
        for (i = 0; i < wc; i++)    // 여학생 전체를 확인하면서
        {
            if (wr[i] == 201 + k) // 해당 학생의 방 번호가 현재 방과 같다면 그 학생의 이름출력
                printf("%s ", wn[i]);
        }
        printf("\n");
    }
}

int main()
{
    int a;
    char mn[10][20];
    int mr[10];
    int mc = 0;
    char wn[10][20];
    int wr[10];
    int wc = 0;
    int room;
    int mp[5] = {0};
    int wp[5] = {0};
    srand(time(NULL)); // 현재 시간을 이용하여 랜덤 시드 값을 설정한다. (랜덤 함수 사용하는 법을 까먹어서 chatGPT의 도움을 받았습니다)

    printf("===========================================\n생활관 호실 배정 프로그램\n===========================================\n");
    while (1)
    {
        printf("메뉴 : 1. 남학생 등록 2. 여학생 등록 0. 종료 > ");
        scanf("%d", &a);
        if (a == 1 && mc + wc < 10) // 남학생 등록을 선택했고 전체 인원이 10명 미만일 때
        {
            printf("학생 이름은?");
            scanf("%s", mn[mc]);                                        // mc번째 남학생 이름을 입력받음
            room = findRoom(mp);                                        // findRoom함수 호출하여 빈 자리가 있는 남학생 방을 랜덤으로 찾음
            mp[room]++;                                                 // 해당 방의 인원 수를 1 증가
            mr[mc] = room + 101;                                        // room(0~4)을 101~105 형태로 계산하여 저장
            printf("%s 학생 %d호실 배정되었습니다.\n", mn[mc], mr[mc]);     // 학생 이름과 배정된 방을 출력
            mc++;                                                       // 남학생 수 1증가
        }
        else if (a == 2 && mc + wc < 10) // 여학생 등록을 선택했고 전체 인원이 10명 미만일 때
        {
            printf("학생 이름은?");
            scanf("%s", wn[wc]);                                        // wc번째 여학생 이름을 입력받음
            room = findRoom(wp);                                        // findRoom함수 호출하여 빈 자리가 있는 여학생 방을 랜덤으로 찾음
            wp[room]++;                                                 // 해당 방의 인원 수를 1 증가
            wr[wc] = room + 201;                                        // room(0~4)을 201~205 형태로 계산하여 저장
            printf("%s 학생 %d호실 배정되었습니다.\n", wn[wc], wr[wc]);     // 학생 이름과 배정된 방을 출력
            wc++;                                                       // 여학생 수 1증가
        }
        else if (a == 0) // 종료 시
        {
            printReport(mn, mr, mc, wn, wr, wc); // 지금까지의 배정 결과를 출력
            break;        
        }
        else
        {
            printf("error\n"); // 잘못된 입력이 들어오거나 전체 인원이 10명 이상일 때 그 이후로는 에러
        }
    }
}