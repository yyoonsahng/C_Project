#include "myheader.h"

void setItem(int flag[][MAP_ROW - 2], struct item *items) {
	int x = 0;
	int y = 0;
	while (1) {
		x = rand() % (MAP_COL - 3);
		y = rand() % (MAP_ROW - 2);
		if ((x < C_COL || y < C_ROW) || ((x + (HINT_COL * 2) > MAP_COL) || y + HINT_ROW > MAP_ROW))
			continue;
		for (int i = y; i < y + HINT_ROW; i++) {
			for (int j = x; j < x + HINT_COL; j++) {
				if (y + HINT_ROW < MAP_ROW - 2 || x + HINT_COL < MAP_COL - 3)
					if(flag[j][i] == 1)
						continue;
			}
		}
		for (int i = y; i < y + HINT_ROW; i++) {
			for (int j = x; j < x + HINT_COL; j++)
				flag[j][i] == 2;
		}
		items->item_x = x;
		items->item_y = y;
		items->item_num = rand() % 4;
		break;
	}
	gotoxy(x, y);
	printf("□■■■□");
	gotoxy(x, ++y);
	printf("■□□□■");
	gotoxy(x, ++y);
	printf("□□■■□");
	gotoxy(x, ++y);
	printf("□□■□□");
	gotoxy(x, ++y);
	printf("□□□□□");
	gotoxy(x, ++y);
	printf("□□■□□");

}

int useItem(int level, int diff, int* x, int* y, int* move, int* life, struct flagPoint* flags, struct item* items) {
	int itemNum = items->item_num;
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