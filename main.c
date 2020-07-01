#include "myheader.h"
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main() {
	int start = 0;
	system("mode con cols=210 lines=105");//화면 크기를 지정한다.
	while (start != 4) {
		start = menu();//게임이 계속 반복 될 수 있도록
	}
	return 0;
}
