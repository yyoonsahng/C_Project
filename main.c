#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define DIFF1 5
#define DIFF2 7
#define DIFF3 12
#define TREASURE 0
#define BACKTOSTART 1
#define RESETFLAG 2
#define RESETPOINT 3
int menu();
void playGame(int, int*);
void makeBackground(int, int*);
void makeFlag(int, int[][18], struct flagPoint *, int);
int checkPoint(int , int , int, struct flagPoint *, int, int*);
int checkFlag(int, int,int*, int*, int, int*, int[][18], struct flagPoint *, int*);
struct flagPoint {
	int x;
	int y;
	int mode;
};
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main() {
	int start = 0;
	system("mode con cols=80 lines=40");
	while (start != 4) {
		start = menu();
	}
	return 0;
}

int menu() {
	int score = 0;
	printf("1. LEVEL 1\n");
	printf("2. LEVEL 2\n");
	printf("3. LEVEL 3\n");
	printf("4. QUIT\n");
	printf("원하시는 메뉴를 입력하세요: ");
	srand(time(NULL));
	int pick = 0;
	scanf("%d", &pick);
	switch (pick)
	{
	case 1:
		playGame(LEVEL1, &score);
		
	case 2:
		playGame(LEVEL2, &score);
	case 3:
		playGame(LEVEL3, &score);
		break;
	default:
		break;
	}
	return pick;
}


void playGame(int level, int *score) {
	int i = 0;
	int x = 1, y = 1, ch;
	int flag[37][18] = {0, };
	int check = -1;
	struct flagPoint flags[12];
	int diff = 0; 
	int levelup = -1;
	int check_flag = -1;
	if (level == 1)
		diff = DIFF1;
	else if (level == 2)
		diff = DIFF2;
	else
		diff = DIFF3;
	makeBackground(level, score);
	makeFlag(level, flag, flags, diff);
	while (1) {
		gotoxy(x, y);
		printf("◆");
		check = checkPoint(x, y, level, flags, diff, &check_flag);
		//printf("%d", check);
		levelup = checkFlag(level, diff, &x, &y, check, score, flag, flags, &check_flag);
		if (levelup == 0)
			break;
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			gotoxy(x, y);
			printf("  ");
		}
		switch (ch) {
		case 72:
			if(y - 1 >= 1)
				y--;
			break;
		case 80:
			if(y + 1 <= 18)
				y++;
			break;
		case 75:
			if(x - 1 >= 1)
				x--;
			break;
		case 77:
			if(x + 1 <= 37)
				x++;
			break;
		}
	}
}

void makeBackground(int level, int *score) {
	system("cls");
	printf("########################################\n");
	for (int i = 0; i < 18; i++) 
		printf("#                                      #\n");
	printf("########################################\n");
	printf("\nSCORE: %d\n", *score);
}

void makeFlag(int level, int flag[][18], struct flagPoint *flags, int diff) {
	int flagNum = diff;
	for (int i = 0; i < flagNum; i++) {
		int x = rand() % 37;
		int y = rand() % 18;
		if (flag[x][y] == 0) {
			flag[x][y] = 1;
			gotoxy(x + 1, y + 1);
			flags[i].x = x + 1;
			flags[i].y = y + 1;
			if (i > RESETPOINT) {
				int a = i % 2;
				flags[i].mode = a + 1;
			}
			else
				flags[i].mode = i;
			printf("▶");
		}
		else if ((x == 0 && y == 0) || flag[x][y] == 1)
			i--;
	}
}

int checkPoint(int x, int y, int level, struct flagPoint* flags, int diff, int *check_flag) {
	int check = -1;
	for (int i = 0; i < diff; i++) {
		if (((flags[i].x == x || flags[i].x == x + 1) || (flags[i].x == x || flags[i].x == x - 1)) && flags[i].y == y) {
			check = flags[i].mode;
			*check_flag = i;
			break;
		}
	}
	return check;
}

int checkFlag(int level, int diff, int *x, int *y, int check, int *score, int flag[][18], struct flagPoint* flags, int *check_flag) {
	int nextlevel = -1;
	int countFlag = 0;
	if (check == 0) {
		system("cls");
		printf("보물발견!!!!!!!!!\n");
		if (level == 1)
			*score += 50;
		else if (level == 2)
			*score += 70;
		else
			*score += 120;
		nextlevel = 0;
	}
	else if (check == 1) {
		gotoxy(*x - 1, *y);
		printf("  ");
		*x = 1;
		*y = 1;
		gotoxy(*x, *y);
		printf("◆");
		flags[*check_flag].mode = -1;
		nextlevel = 1;
	}
	else if (check == 2) {
		for (int i = 0; i < diff; i++) {//diff가 아니라 지금까지 남은 거로 해야함
			if (flags[i].mode != -1)
				countFlag++;
			if (flags[i].x == 0 && flags[i].y == 0)
				break;
				gotoxy(flags[i].x, flags[i].y);
			flag[flags[i].x - 1][flags[i].y - 1] = 0;
			printf("  ");
			flags[i].x = 0;
			flags[i].y = 0;
			flags[i].mode = -1;
		}
		makeFlag(level, flag, flags, countFlag - 1);
		gotoxy(*x, *y);
		printf("◆");
		nextlevel = 2;
	}
	else if (check == 3) {
		printf("  ");
		gotoxy(*x - 1, *y);
		printf("  ");
		*score = 0;
		gotoxy(0, 21);
		printf("SCORE: %d  \n", *score);
		gotoxy(*x, *y);
		printf("◆");
		flags[*check_flag].mode = -1;
		nextlevel = 3;
	}
	return nextlevel;
}