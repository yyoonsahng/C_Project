#include "myheader.h"
void drawTitle() {//Title을 그린다
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

void makeBackground(int level, int* score, int* move, int* life) {//게임의 배경, 울타리를 그려준다.
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

void drawCharacter(int x, int y) {//플레이어(마리오)를 출력한다.
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
void eraseCharacter(int x, int y) {//x,y 좌표를 입력받아 플레이어을 지워준다.
	for (int i = 0; i < C_ROW; i++) {
		gotoxy(x, y);
		for (int i = 0; i < C_COL; i++)
			printf(" ");
		y++;
		printf("\n");
	}
}

void makeFlag(int level, int flag[][MAP_ROW - 2], struct flagPoint* flags, int diff) {
	//깃발을 만들어준다.
	int flagNum = diff;
	for (int i = 0; i < flagNum; i++) {
		int x = (rand() % (MAP_COL - 3));//랜덤한 좌표를 입력받는다.
		int y = rand() % (MAP_ROW - 2);
		if ((x < C_COL || y < C_ROW) || flag[x][y] == 1)//이미 생성된 깃발, 플레이어의 위치와 중복되지 않도록
			i--;
		else if (flag[x][y] == 0) {//깃발을 생성
			flag[x][y] = 1;
			gotoxy(x + 1, y + 1);
			flags[i].x = x + 1;//깃발의 좌표
			flags[i].y = y + 1;
			if (i > RESETPOINT) {//깃발의 유형 배정, 
				int a = i % 2;
				flags[i].mode = a + 1;
			}
			else
				flags[i].mode = i;
			printf("▶");
		}
	}
}
void eraseItem(struct item* items) {//item을 획득한 경우 아이템 그림을 지우기 위해
	gotoxy(items->item_x, items->item_y);
	for (int i = 0; i < HINT_ROW; i++) {
		gotoxy(items->item_x, items->item_y + i);
		for (int j = 0; j < HINT_COL; j++) {
			printf("  ");
		}
	}
}

void makeStar(int level) {//게임, 레벨 클리어시 축하 문구를 출력한다.
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
