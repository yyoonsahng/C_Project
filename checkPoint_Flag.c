#include "myheader.h"

int checkPoint(int x, int y, int level, int able_item, struct flagPoint* flags, struct item* items, int diff, int* check_flag) {
	int check = -1;
	int br = 0;
	if (!able_item) {
		if ((items->item_x <= x + C_COL && items->item_x > x) && (items->item_y <= y + C_ROW && items->item_y >= y)) {
			eraseItem(items);
			return 4;
		}
		else if ((items->item_x <= x + C_COL && items->item_x > x) && (items->item_y + HINT_ROW <= y + C_ROW && items->item_y + HINT_ROW >= y)) {
			eraseItem(items);
			return 4;
		}
		else if ((items->item_x + HINT_COL <= x + C_COL && items->item_x + HINT_COL > x) && (items->item_y <= y + C_ROW && items->item_y >= y)) {
			eraseItem(items);
			return 4;
		}
		else if ((items->item_x + HINT_COL <= x + C_COL && items->item_x + HINT_COL > x) && (items->item_y + HINT_ROW <= y + C_ROW && items->item_y + HINT_ROW >= y)) {
			eraseItem(items);
			return 4;
		}
	}
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

int checkFlag(int level, int diff, int* x, int* y, int check, int* score, int flag[][18], struct flagPoint* flags, int* check_flag) {
	int nextlevel = -1;
	int countFlag = 0;
	if (check == 0) {
		system("cls");
		gotoxy(60, 22);
		makeStar(level);
		Sleep(3000);
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