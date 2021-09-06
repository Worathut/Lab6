#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<windows.h>

void gotoxy(int x, int y) {
	//setPosition
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(int fg, int bg) {
	//setColor
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void setcursor(bool visible) {
	//setCursor
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void erase_Bg(int x, int y) {
	//erase background
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void draw_ship(int x, int y) {
	//draw ship
	setcolor(2, 4);
	gotoxy(x, y);
	printf(" <-0-> ");
}

void erase_ship(int x, int y) {
	//erase ship
	gotoxy(x, y);
	printf("       ");
}

void draw_bullet(int x, int y) {
	//draw bullet
	setcolor(2, 0);
	gotoxy(x, y);
	printf("!");
}

void erase_bullet(int x, int y) {
	//erase bullet
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

struct Bullet {
	int Active = 0;
	int x = 0, y = 0;
};

int main() {
	char ch = ' ';
	int action = 0;
	int x = 38, y = 29;
	Bullet bullets[5];

	draw_ship(x, y);
	setcursor(0);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a'|| ch == 'A' || ch == '¿' || ch == 'Ä') {
				action = 1;
			}
			if (ch == 'd'|| ch == 'D' || ch == '¡' || ch == '¯') {
				action = 2;
			}
			if (ch == 's'|| ch == 'S' || ch == 'Ë' || ch == '¦') {
				action = 3;
			}
			if (ch == ' ') {
				for (int i = 0; i < 5; i++) {
					if (bullets[i].Active == 0)
					{
						bullets[i].Active = 1;
						bullets[i].x = x + 3;
						bullets[i].y = y;
						break;
					}
				}
			}
			fflush(stdin);
		}

		for (int i = 0; i <= 4; i++) {
			if (bullets[i].Active == 1)
			{
				erase_bullet(bullets[i].x, bullets[i].y);
				if (bullets[i].y > 0) {
					draw_bullet(bullets[i].x, --bullets[i].y);
				}
				else {
					bullets[i].Active = 0;
				}
			}
		}

		if (action == 1 && x > 0)
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(--x, y);

		}
		if (action == 2 && x < 80)
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(++x, y);
		}
		if (action == 3)
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(x, y);
		}

	Sleep(100);
	} while (ch != 'x');
	return 0;
}