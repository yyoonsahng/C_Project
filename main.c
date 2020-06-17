#include "myheader.h"
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
	system("mode con cols=200 lines=100");
	while (start != 4) {
		start = menu();
	}
	return 0;
}

int menu() {
	int score = 0;
	int pick = 0;
	int life = 1;
	printf("1. LEVEL 1\n");
	printf("2. LEVEL 2\n");
	printf("3. LEVEL 3\n");
	printf("4. QUIT\n");
	printf("원하시는 메뉴를 입력하세요: ");
	srand(time(NULL));
	scanf("%d", &pick);
	switch (pick)
	{
	case 1:
		if (playGame(LEVEL1, &score, &life) == 0)
			break;
	case 2:
		if (playGame(LEVEL2, &score, &life) == 0)
			break;
	case 3:
		playGame(LEVEL3, &score, &life);
		break;
	default:
		break;
	}
	return pick;
}

void drawCharacter(int x, int y) {
	gotoxy(x, y);
	printf("   ■■■■■");
	gotoxy(x, ++y);
	printf("  ■■■■■■■■■");
	gotoxy(x, ++y);
	printf("  ■■■□□■□");
	gotoxy(x, ++y);
	printf(" ■□■■□□□■□□□");
	gotoxy(x, ++y);
	printf("   □□□□□□□");
	gotoxy(x, ++y);
	printf("■■■■■■■■");
	gotoxy(x, ++y);
	printf("□□■■■■■■■■□□");
	gotoxy(x, ++y);
	printf("  ■■■  ■■■");
	gotoxy(x, ++y);
	printf("■■■■    ■■■■");
}

void eraseCharacter(int x, int y) {
	for (int i = 0; i < C_ROW; i++) {
		gotoxy(x, y);
		for (int i = 0; i < C_COL; i++)
			printf(" ");
		y++;
		printf("\n");
	}
}
int playGame(int level, int *score, int *life) {
	int i = 0;
	int x = 1, y = 1, ch;
	int flag[MAP_COL - 3][MAP_ROW - 2] = {0, };
	int check = -1;
	struct flagPoint flags[12];
	int diff = 0; 
	int levelup = -1;
	int check_flag = -1;
	int kbHit = 0;
	int saveMove = 0;
	int con = -1;
	if (level == 1) {
		diff = DIFF1;
		kbHit = KBHIT1;
		saveMove = KBHIT1;
	}
	else if (level == 2) {
		diff = DIFF2;
		kbHit = KBHIT2;
		saveMove = KBHIT2;
	}
	else {
		diff = DIFF3;
		kbHit = KBHIT3;
		saveMove = KBHIT3;
	}
	makeBackground(level, score, &kbHit, life);
	makeFlag(level, flag, flags, diff);
	while (1) {
		drawCharacter(x, y);
		gotoxy(x, y);
		check = checkPoint(x, y, level, flags, diff, &check_flag);
		//printf("%d", check);
		if (kbHit < 1) {
			if (--(*life) == 0) {
				system("cls");
				printf("Game Over\n");
				return 0;
			}
			else {
				kbHit = saveMove;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("LIFE: %d", *life);
			}
		}
		levelup = checkFlag(level, diff, &x, &y, check, score, flag, flags, &check_flag);
		if (levelup == 0)
			break;
		ch = _getch();
		if (ch == 0) {
			ch = _getch();
			if (ch == 59) {
				con = useItem(level, diff, &x, &y, &kbHit, life, flags);
				if (con == 0)
					return 0;
				else if(con == 2)
					return 2;
			}
		}
		if (ch == 224) {
			ch = _getch();
			eraseCharacter(x, y);
			gotoxy(x, y);
		}
		switch (ch) {
		case 72:
			if (y - 1 >= 1) {
				y--;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 80:
			if (y + 1 + C_ROW <= MAP_ROW - 1) {
				y++;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 75:
			if (x - 1 >= 1) {
				x--;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 77:
			if (x + 1 + C_COL <= MAP_COL - 2) {
				x++;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("현재 좌표: %d   %d  ", x, y);
			}
			break;
		}
	}
	return 1;
}

int useItem(int level, int diff, int *x, int *y, int *move, int *life, struct flagPoint *flags) {
	int itemNum = rand() % 4;
	int result = 1;
	int countFlag = 0;
	switch (itemNum) {
	case 0:
		if (level == 1)
			*move = KBHIT1;
		else if (level == 2)
			*move = KBHIT2;
		else if (level == 3)
			*move = KBHIT3;
		gotoxy(0, MAP_ROW + 1);
		printf("남은 이동 횟수: %d  ", *move);
		break;

	case 1:
		for (int i = 0; i < diff; i++) {
			if (flags[i].mode == 0) {
				gotoxy(flags[i].x, flags[i].y);
				printf("★");
				gotoxy(*x, *y);
			}
		}
		break;
	case 2:
		for (int i = 0; i < diff; i++) {
			if (flags[i].mode != -1)
				countFlag++;
		}
		if (countFlag > 3) {
			for (int i = countFlag - 1; i > countFlag - 4; i--) {
				gotoxy(flags[i].x, flags[i].y);
				printf("  ");
				flags[i].mode = -1;
			}
		}
		else {
			result = 2;
		}
		break;
	case 3:
		(*life)++;
		gotoxy(0, MAP_ROW + 2);
		printf("LIFE: %d", *life);
		break;
	}
	return result;
}

void makeBackground(int level, int *score, int *move, int *life) {
	system("cls");
	for(int i =0; i< MAP_COL;i++){
		printf("#");
	}
	printf("\n");
	for (int i = 0; i < MAP_ROW - 2; i++) {
		printf("#");
		for (int i = 0; i < MAP_COL - 2; i++) 
			printf(" ");
		printf("#\n");
	}
	for (int i = 0; i < MAP_COL; i++) {
		printf("#");
	}
	printf("\nSCORE: %d\n", *score);
	printf("남은 이동 횟수: %d  \n", *move);
	printf("LIFE: %d", *life);
	
}

void makeFlag(int level, int flag[][MAP_ROW - 2], struct flagPoint *flags, int diff) {
	int flagNum = diff;
	for (int i = 0; i < flagNum; i++) {
		int x = rand() % (MAP_COL - 3);
		int y = rand() % (MAP_ROW - 2);
		if ((x < C_COL || y < C_ROW) || flag[x][y] == 1)
			i--;
		else if (flag[x][y] == 0) {
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
	}
}

int checkPoint(int x, int y, int level, struct flagPoint* flags, int diff, int *check_flag) {
	int check = -1;
	int br = 0;
	for (int i = 0; i < diff; i++) {
		for (int j = 0; j < C_ROW; j++) {
			for (int k = 0; k < C_COL; k++) {
				if (flags[i].x == x + k && flags[i].y == y + j && flags[i].mode != -1) {
					check = flags[i].mode;
					*check_flag = i;
					br = 1;
					break;
				}
			}
			if (br == 1)
				break;
		}
		if (br == 1)
			break;
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
		eraseCharacter(*x, *y);
		*x = 1;
		*y = 1;
		drawCharacter(*x, *y);
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
		//gotoxy(*x, *y);
		//printf("◆");
		nextlevel = 2;
	}
	else if (check == 3) {
		printf("  ");
		gotoxy(*x - 1, *y);
		printf("  ");
		*score = 0;
		gotoxy(0, MAP_ROW);
		printf("SCORE: %d  \n", *score);
		//gotoxy(*x, *y);
		//printf("◆");
		flags[*check_flag].mode = -1;
		nextlevel = 3;
	}
	return nextlevel;
}
