#include "myheader.h"
void drawTitle() {
	gotoxy(50, 15);
	printf("■■■  ■    ■  ■■■  ■■■  ■■■    ■    ■      ■       ■■■    ■■■    ■■■");
	gotoxy(50, 16);
	printf("■      ■    ■  ■  ■  ■      ■  ■    ■ ■ ■    ■  ■     ■  ■      ■    ■      ■");
	gotoxy(50, 17);
	printf("■■■  ■    ■  ■■■  ■■■  ■■      ■    ■    ■■■     ■■        ■    ■      ■");
	gotoxy(50, 18);
	printf("    ■  ■    ■  ■      ■      ■  ■    ■    ■   ■     ■   ■  ■      ■    ■      ■");
	gotoxy(50, 19);
	printf("■■■    ■■    ■      ■■■  ■    ■  ■    ■  ■       ■  ■    ■  ■■■    ■■■\n");
	gotoxy(60, 21);
}

void makeBackground(int level, int* score, int* move, int* life) {
	system("cls");
	for (int i = 0; i < MAP_COL; i++) {
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
	gotoxy(100, MAP_ROW + 2);
	printf("LEVEL %d", level);
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

void makeFlag(int level, int flag[][MAP_ROW - 2], struct flagPoint* flags, int diff) {
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
void eraseItem(struct item* items) {
	gotoxy(items->item_x, items->item_y);
	for (int i = 0; i < HINT_ROW; i++) {
		gotoxy(items->item_x, items->item_y + i);
		for (int j = 0; j < HINT_COL; j++) {
			printf("  ");
		}
	}
}

void makeStar(int level) {
	gotoxy(80, 22);
	printf("      **");
	gotoxy(80, 23);
	printf("      **");
	gotoxy(80, 24);
	printf("**************");
	gotoxy(80, 25);
	printf("  **********");
	gotoxy(80, 26);
	printf("    ******");
	gotoxy(80, 27);
	printf("  ****  ****");
	gotoxy(80, 28);
	printf("  **      **");
	if (level == 3) {
		gotoxy(40, 30);
		printf("  ■■■      ■      ■      ■  ■■■    ■■■  ■        ■■■      ■      ■■■    ■■■");
		gotoxy(40, 31);
		printf("■           ■ ■    ■  ■  ■  ■      ■        ■        ■         ■ ■    ■   ■    ■■");
		gotoxy(40, 32);
		printf("■  ■■    ■■■    ■      ■  ■■■  ■        ■        ■■■    ■■■    ■■        ■");
		gotoxy(40, 33);
		printf("■    ■   ■    ■   ■      ■  ■      ■        ■        ■       ■    ■   ■  ■");
		gotoxy(40, 34);
		printf("  ■■■  ■      ■  ■      ■  ■■■    ■■■  ■■■■  ■■■  ■      ■  ■    ■    ■");
	}
	else {
		gotoxy(40, 30);
		printf("■        ■■■  ■       ■  ■■■  ■          ■■■  ■        ■■■      ■      ■■■    ■■■");
		gotoxy(40, 31);
		printf("■        ■       ■     ■   ■      ■        ■        ■        ■         ■ ■    ■   ■    ■■");
		gotoxy(40, 32);
		printf("■        ■■■    ■   ■    ■■■  ■        ■        ■        ■■■    ■■■    ■■        ■");
		gotoxy(40, 33);
		printf("■        ■         ■ ■     ■      ■        ■        ■        ■       ■    ■   ■  ■");
		gotoxy(40, 34);
		printf("■■■■  ■■■      ■       ■■■  ■■■■    ■■■  ■■■■  ■■■  ■      ■  ■    ■    ■");
	}
}