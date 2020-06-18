#include "myheader.h"
int menu() {
	int score = 0;
	int pick = 0;
	int life = 1;
	system("cls");
	drawTitle();
	printf("1. LEVEL 1");
	gotoxy(60, 22);
	printf("2. LEVEL 2");
	gotoxy(60, 23);
	printf("3. LEVEL 3");
	gotoxy(60, 24);
	printf("4. QUIT");
	gotoxy(60, 25);
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