#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define HINT_ROW 6//아이템의 행
#define HINT_COL 5//아이템 열
#define MAP_COL 190//게임 맵의 행
#define MAP_ROW 45//게임 맵의 열
#define C_ROW 9//케릭터의 행
#define C_COL 24//케릭터의 열
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define DIFF1 5//레벨에 따른 깃발 개수
#define DIFF2 7
#define DIFF3 12
#define KBHIT1 700//레벨에 따른 이동 가능 횟수
#define KBHIT2 500
#define KBHIT3 300

#define TREASURE 0//깃발 유형에 따른 구분
#define BACKTOSTART 1
#define RESETFLAG 2
#define RESETPOINT 3
struct flagPoint {//깃발 정보를 저장할 구조체
	int x;
	int y;
	int mode;
};
struct item {//아이템 정보를 저장할 구조체
	int item_x;
	int item_y;
	int item_num;
};
int menu();
int playGame(int, int*, int*);
void makeBackground(int, int*, int*, int*);
void makeFlag(int, int[][MAP_ROW - 2], struct flagPoint*, int);
int checkPoint(int, int, int, int, struct flagPoint*, struct item *,int, int*);
int checkFlag(int, int, int*, int*, int, int*, int[][18], struct flagPoint*, int*);
int useItem(int, int, int*, int*, int*, int*, struct flagPoint*, struct item *);
void drawCharacter(int, int);
void eraseCharacter(int, int);
void setItem(int[][MAP_ROW - 2], struct item *);
void eraseItem(struct item*);
void drawTitle();
void makeStar(int);
