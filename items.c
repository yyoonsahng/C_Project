#include "myheader.h"

void setItem(int flag[][MAP_ROW - 2], struct item *items) {//아이템을 세팅한다. 레벨마다 새로 세팅되서 달라진다.
	int x = 0;
	int y = 0;
	while (1) {
		x = rand() % (MAP_COL - 3);//랜덤으로 좌표 하나씩 저장
		y = rand() % (MAP_ROW - 2);
		//플레이어의 시작 위치, 그리고 맵의 크기를 벗어난곳에 아이템이 그려지지 않도록 한다.
		if ((x < C_COL || y < C_ROW) || ((x + (HINT_COL * 2) > MAP_COL - 1) || y + HINT_ROW > MAP_ROW - 1))
			continue;
		//깃발의 위치와 중복되지 않도록 확인한다.
		for (int i = y; i < y + HINT_ROW; i++) {
			for (int j = x; j < x + HINT_COL; j++) {
				if (y + HINT_ROW < MAP_ROW - 2 || x + HINT_COL < MAP_COL - 3)
					if(flag[j][i] == 1)
						continue;
			}
		}
		//flag배열에 아이템의 위치를 표시한다.
		for (int i = y; i < y + HINT_ROW; i++) {
			for (int j = x; j < x + HINT_COL; j++)
				flag[j][i] == 2;
		}
		//아이템 구조체 변수에 아이템의 좌표와 아이템 종류를 배정한다.
		items->item_x = x;
		items->item_y = y;
		items->item_num = rand() % 4;
		break;
	}
	//아이템을 해당 좌표에 그린다.
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
	//아이템 종류에 따라서 아이템을 사용한다.
	int itemNum = items->item_num;
	int result = 1;
	int countFlag = 0;
	switch (itemNum) {
	case 0://0번 아이템인 경우, 현재 남은 가능 이동 횟수를 레벨에 따라 다시 full로 복구한다.
		if (level == 1)
			*move = KBHIT1;
		else if (level == 2)
			*move = KBHIT2;
		else if (level == 3)
			*move = KBHIT3;
		gotoxy(0, MAP_ROW + 1);
		printf("남은 이동 횟수: %d  ", *move);
		break;

	case 1://1번 아이템인 경우, 보물의 위치를 별로 표시해서 사용자로 하여금 바로 보물의 위치를 알 수 있도록 한다.
		gotoxy(flags[0].x, flags[0].y);//flags[0]이 보물의 깃발
		printf("★");
		gotoxy(*x, *y);
		break;
	case 2://2번 아이템인 경우, 깃발의 개수를 줄여준다
		for (int i = 0; i < diff; i++) {//현재 남은 깃발의 개수를 count
			if (flags[i].mode != -1)
				countFlag++;
		}
		if (countFlag > 3) {//3개 초과인 경우
			for (int i = countFlag - 1; i > countFlag - 4; i--) {
				//flags배열(깃발 구조체 배열)에서 뒤에서부터 3개를 지운다. flags[0]에 보물을 저장하고 있기 때문에
				gotoxy(flags[i].x, flags[i].y);
				printf("  ");
				flags[i].mode = -1;
			}
		}
		else {//3개 이하인 경우, 다음 레벨로 넘어간다.
			result = 2;
		}
		break;
	case 3://3번 아이템인 경우
		//life를 1 늘려준다
		(*life)++;
		gotoxy(0, MAP_ROW + 2);
		printf("LIFE: %d", *life);
		break;
	}
	return result;
}
