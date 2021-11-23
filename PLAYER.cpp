#include "Header.h"
using namespace std;


player::player(int x, int y, char head, char body) : x(x), y(y), ix(x), iy(y), head(head), body(body)
{
    gotoxy(x, y);
    cout << body;
    gotoxy(x, y - 1);
    cout << head;
}

void player::reset() {
    gotoxy(x, y); cout << " ";
    gotoxy(x, y - 1); cout << " ";
    x = ix;
    y = iy;
    gotoxy(x, y); cout << body;
    gotoxy(x, y - 1); cout << head;
}

char player::run()
{
    gotoxy(x, y);
    cout << body;
    gotoxy(x, y - 1);
    cout << head;

    if (_kbhit())
    {
        char a = _getch();
        switch (a)
        {
        case 'w':
            gotoxy(x, y);
            cout << " ";
            gotoxy(x, y - 1);
            cout << " ";
            if (y > 0)
                y--;
            gotoxy(x, y);
            cout << body;
            gotoxy(x, y - 1);
            cout << head;
            break;
        case 'a':
            gotoxy(x, y);
            cout << " ";
            gotoxy(x, y - 1);
            cout << " ";
            if (x > 0)
                x--;
            gotoxy(x, y);
            cout << body;
            gotoxy(x, y - 1);
            cout << head;
            break;
        case 's':
            gotoxy(x, y);
            cout << " ";
            gotoxy(x, y - 1);
            cout << " ";
            if (y < ConsoleHeight - 1)
                y++;
            gotoxy(x, y);
            cout << body;
            gotoxy(x, y - 1);
            cout << head;
            break;
        case 'd':
            gotoxy(x, y);
            cout << " ";
            gotoxy(x, y - 1);
            cout << " ";
            if (x < ConsoleWidth - 1)
                x++;
            gotoxy(x, y);
            cout << body;
            gotoxy(x, y - 1);
            cout << head;
            break;
        default:
            return a;
        }
    }
    return '.';
}

// cập nhật vị trí người chơi
OXY player::position()
{
    return OXY(x, y);
}

void inGame::saveFile() {
    while (1) {
        gotoxy(1, 1);
        cout << "-----------------------------------------------------------------------------";
        gotoxy(1, 2);
        cout << "enter file location:                                                         ";
        gotoxy(1, 3);
        cout << "enter file name:                                                             ";
        gotoxy(1, 4);
        cout << "-----------------------------------------------------------------------------";

        gotoxy(24, 2);
        string dir;
        cin >> dir;
        gotoxy(20, 3);
        string file;
        cin >> file;

        ofstream ofs(dir + "\\" + file, ios::binary);
        if (!ofs.good()) {
            gotoxy(15, 4);
            cout << "|     file cannot open      |";
        }
        else {
            ofs.write((char*)&score, 4);
            ofs.write((char*)&level_, 1);
            int32_t s = land_.size();
            ofs.write((char*)&s, 4);
            for (int i = 0; i < land_.size(); i++)
            {
                bool a = land_[i];
                ofs.write((char*)&a, 1);
            }
        }
        ofs.close();
        gotoxy(1, 5);
        cout << "re-save file? y/n: ";
        char a;
        cin >> a;
        if (a == 'n') break;
    }

    gotoxy(1, 1);
    cout << "                                                                             ";
    gotoxy(1, 2);
    cout << "                                                                             ";
    gotoxy(1, 3);
    cout << "                                                                             ";
    gotoxy(1, 4);
    cout << "                                                                             ";
    gotoxy(1, 5);
    cout << "                            ";
}