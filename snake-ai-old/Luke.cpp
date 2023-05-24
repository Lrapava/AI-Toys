#include "cmdef.cpp"
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>

void SetColor(int ForgC) {
     
	WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
     }

}

#define _pressed =pressed(
bool pressed(char c) {
	if (GetKeyState(c)  & 0x8000) return 1;
	return 0;
}

#define _kbget kbget(
bool kbget(char &c) {
	bool b = false;
	if (kbhit()) {
		c = getch();
		b = true;
	}
	return b;
}

#define _gotoxy gotoxy(
void gotoxy(int column, int line) {
  COORD coord;
  
  coord.X = column;
  coord.Y = line;
  
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}

int mouseX() {
	POINT point;
	GetCursorPos(&point);
	return point.x;
}

int mouseY() {
	POINT point;
	GetCursorPos(&point);
	return point.y;
}

bool lClick() {
	
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0) {
		return true;
   }

   return false;

}
bool rClick() {
	
	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0) {
		return true;
   }

   return false;

}
