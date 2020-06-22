#include "myheader.h"

int checkPoint(int x, int y, int level, int able_item, struct flagPoint* flags, struct item* items, int diff, int* check_flag) {
	//현재 플레이어의 위치를 검사해서 반환한다.
	int check = -1;
	int br = 0;
	if (!able_item) {//아이템 박스와 접촉했는지 확인
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
	for (int i = 0; i < diff; i++) {//깃발과 접촉했는지 확인한다
		for (int j = 0; j < C_ROW; j++) {
			for (int k = 0; k < C_COL; k++) {
				if (flags[i].x == x + k && flags[i].y == y + j && flags[i].mode != -1) {
					check = flags[i].mode;//접촉했다면 깃발의 유형과 인덱스를 반환. 인덱스는 포인터를 이용해 반환한다.
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
	//checkPoint가 반환한 값이 깃발인 경우 깃발에 따라 벌칙 혹은 다음 레벨로 넘어간다.
	int nextlevel = -1;
	int countFlag = 0;
	if (check == 0) {//보물인 경우
		system("cls");
		gotoxy(60, 22);
		makeStar(level);//축하문구를 3초간 띄운다
		Sleep(3000);
		if (level == 1)//레벨에 따른 점수 부여
			*score += 50;
		else if (level == 2)
			*score += 70;
		else
			*score += 120;
		nextlevel = 0;
	}
	else if (check == 1) {//벌칙1 플레이어를 최초의 위치로 되돌린다.
		gotoxy(flags[*check_flag].x, flags[*check_flag].y);//깃발을 지운다.
		printf("  ");
		eraseCharacter(*x, *y);//현재 위치에서 플레이어를 지운다
		*x = 1;
		*y = 1;
		drawCharacter(*x, *y);//1,1로 가서 플레이어를 다시 그린다.
		flags[*check_flag].mode = -1;//깃발의 유형을 -1로 바꾼다.
		nextlevel = 1;
	}
	else if (check == 2) {//벌칙 2 현재 남은 깃발에 대해서 다시 배치한다.
		gotoxy(flags[*check_flag].x, flags[*check_flag].y);//깃발을 지운다.
		printf("  ");
		for (int i = 0; i < diff; i++) {//반복문을 돌면서 깃발 구조체 배열에 접근하면서 현재 남은 깃발 개수를 파악하고
			//남은 깃발에 대해서 다 초괴화한다.
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
		makeFlag(level, flag, flags, countFlag - 1);//남은 깃발 개수에 대해서 다시 깃발을 생성한다.
		//gotoxy(*x, *y);
		//printf("◆");
		nextlevel = 2;
	}
	else if (check == 3) {//벌칙 3 현재 스코어를 초기화
		gotoxy(flags[*check_flag].x, flags[*check_flag].y);
		printf("  ");
		printf("  ");
		gotoxy(*x - 1, *y);
		printf("  ");
		*score = 0;//스코어를 0으로 초기화한다.
		gotoxy(0, MAP_ROW);
		printf("SCORE: %d  \n", *score);
		//gotoxy(*x, *y);
		//printf("◆");
		flags[*check_flag].mode = -1;
		nextlevel = 3;
	}
	return nextlevel;
}
