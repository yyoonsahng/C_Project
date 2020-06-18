#include "myheader.h"
int playGame(int level, int* score, int* life) {
	int i = 0;
	int able_item = 0;
	int x = 1, y = 1, ch;
	struct item items;
	int flag[MAP_COL - 3][MAP_ROW - 2] = { 0, };
	int check = -1;
	struct flagPoint flags[13];
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
	setItem(flag, &items);
	while (1) {
		drawCharacter(x, y);
		gotoxy(x, y);
		check = checkPoint(x, y, level, able_item, flags, &items, diff, &check_flag);
		if (check == 4) {
			gotoxy(100, MAP_ROW);
			printf("아이템 획득! : ");
			switch (items.item_num)
			{
			case 0:
				printf("이동 횟수 복구");
				break;
			case 1:
				printf("보물 위치 확인 (★)");
				break;
			case 2:
				printf("깃발 개수 줄이기");
				break;
			case 3:
				printf("LIFE 1 추가");
			}
			able_item = 1;
		}
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
			if (ch == 59 && able_item == 1) {
				con = useItem(level, diff, &x, &y, &kbHit, life, flags, &items);
				able_item++;
				if (con == 0)
					return 0;
				else if (con == 2)
					return 2;
				gotoxy(100, MAP_ROW);
				printf("아이템 사용 완료!               ");
			}
			else if (ch == 59 && able_item == 2) {
				gotoxy(100, MAP_ROW + 1);
				printf("이미 아이템을 사용했습니다!");
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
				printf("\n현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 80:
			if (y + 1 + C_ROW <= MAP_ROW - 1) {
				y++;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("\n현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 75:
			if (x - 1 >= 1) {
				x--;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("\n현재 좌표: %d   %d  ", x, y);
			}
			break;
		case 77:
			if (x + 1 + C_COL <= MAP_COL - 1) {
				x++;
				kbHit--;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("\n현재 좌표: %d   %d  ", x, y);
			}
			break;
		}
	}
	return 1;
}