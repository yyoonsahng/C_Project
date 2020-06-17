#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define MAP_COL 190
#define MAP_ROW 45
#define C_ROW 9
#define C_COL 24
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define DIFF1 5
#define DIFF2 7
#define DIFF3 12
#define KBHIT1 700
#define KBHIT2 500
#define KBHIT3 300
#define TREASURE 0
#define BACKTOSTART 1
#define RESETFLAG 2
#define RESETPOINT 3
int menu();
int playGame(int, int*, int*);
void makeBackground(int, int*, int*, int*);
void makeFlag(int, int[][MAP_ROW - 2], struct flagPoint*, int);
int checkPoint(int, int, int, struct flagPoint*, int, int*);
int checkFlag(int, int, int*, int*, int, int*, int[][18], struct flagPoint*, int*);
int useItem(int, int, int*, int*, int*, int*, struct flagPoint*);
void drawCharacter(int, int);
void eraseCharacter(int, int);
