#include "myheader.h"
int playGame(int level, int* score, int* life) {//레벨, 점수, 셍명을 입력받아 게임을 실행한다.
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
	if (level == 1) {//레벨에 따라서 깃발의 개수 배정
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
	makeBackground(level, score, &kbHit, life);//게임 배경을 그린다
	makeFlag(level, flag, flags, diff);//깃발을 배치한다.
	setItem(flag, &items);//아이템 종류를 결정하고 아이템을 배치한다.
	while (1) {
		drawCharacter(x, y);//플레이어를 해당 좌표에 출력한다.
		gotoxy(x, y);
		//현재 플레이어의 위치에 깃발 혹은 아이템이 있는지 체크
		check = checkPoint(x, y, level, able_item, flags, &items, diff, &check_flag);
		//아이템이라면
		if (check == 4) {//아이템 종류에 따른 출력
			gotoxy(100, MAP_ROW);
			printf("아이템 획득! (F1키로 사용): ");
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
		if (kbHit < 1) {//이동 가능 횟수를 다 사용한 경우
			if (--(*life) == 0) {//생명이 0이 된경우 -> 게임오버
				system("cls");
				printf("Game Over\n");
				return 0;
			}
			else {//생명이 남은 경우 -> 생명만 줄어들고 이동 가능 횟수는 복구
				kbHit = saveMove;
				gotoxy(0, MAP_ROW + 1);
				printf("남은 이동 횟수: %d  \n", kbHit);
				printf("LIFE: %d", *life);
			}
		}
		//깃발에 따른 벌칙 혹은 다음 레벨로 가는 행동을 수행한다.
		levelup = checkFlag(level, diff, &x, &y, check, score, flag, flags, &check_flag);
		if (levelup == 0)//레벨을 클리어한 경우
			break;
		ch = _getch();//사용자 키보드 입력받는다.
		if (ch == 0) {//F1 키를 누른 경우(아이템 사용)
			ch = _getch();
			if (ch == 59 && able_item == 1) {//아이템을 획득하고 F1키를 누른 경우
				con = useItem(level, diff, &x, &y, &kbHit, life, flags, &items);
				able_item++;
				if (con == 0)
					return 0;
				else if (con == 2)
					return 2;
				gotoxy(100, MAP_ROW);
				printf("아이템 사용 완료!                                   ");
			}
			else if (ch == 59 && able_item == 2) {//아이템을 이미 사용했지만 F1키를 누른 경우
				gotoxy(100, MAP_ROW + 1);
				printf("이미 아이템을 사용했습니다!");
			}
		}
		if (ch == 224) {//방향키를 누른 경우
			ch = _getch();
			eraseCharacter(x, y);//플레이어를 현재 위치에서 지운다.
			gotoxy(x, y);
		}
		switch (ch) {//플레이어 좌표 이동, 남은 이동 간으 횟수 갱신
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
