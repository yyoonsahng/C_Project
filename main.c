#include "myheader.h"
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main() {
	int start = 0;
	system("mode con cols=210 lines=105");
	while (start != 4) {
		start = menu();
	}
	return 0;
}
