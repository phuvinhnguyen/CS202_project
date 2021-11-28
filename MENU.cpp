/*
#include "MENU.h"
using namespace std;


const int choose_num = 4;

void menu::gameTitle(int x, int y) {
	gotoxy(x, y);
	cout << "PASS AWAY GAME";
}
int menu::button(int x, int y) {
	gotoxy(x, y);
	cout << "new game";
	gotoxy(x, y + 1);
	cout << "load game";
	gotoxy(x, y + 2);
	cout << "volume";
	gotoxy(x, y + 3);
	cout << "exit";

	int choose = choose_num * 2;

	while (1) {
		if (_kbhit()) {
			char getk = _getch();

			if (getk == 'w') {
				choose--;
			}
			else if (getk == 's') {
				choose++;
			}
			else if (getk == 'y') {
				return choose % choose_num;
			}

			int a = choose % choose_num;
			if (choose == choose_num) {
				choose = choose_num * 2;
			}

			for (int i = 0; i < choose_num; i++) {
				gotoxy(x - 2, y + i);
				cout << " ";
			}

			gotoxy(x - 2, y + a);
			cout << ">";
		}
	}
}
string menu::linkBoard(int x, int y) {
	gotoxy(x, y);
	cout << "enter link to your file: ";
	string str;
	cin >> str;
	return str;
}
void menu::run() {
	SetWindowSize(ConsoleWidth, ConsoleHeight);
	hidecursor();
	bool sound = 1;

	while (1) {
		gameTitle(3, 2);
		int ch = button(5, 6);
		inGame a;
		string dir;

		switch (ch) {
		case 0:
			a.loadGame(1, "", sound);
			system("cls");
			break;
		case 1:
			dir = linkBoard(5, 12);
			a.loadGame(1, dir, sound);
			system("cls");
			break;
		case 2:
			sound = !sound;
			break;
		case 3:
			return;
		}
	}
}
*/