#include "PLAYER.h"
#include "EXTRA.h"
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
            if (y > 2)
            {
                gotoxy(x, y);
                cout << " ";
                gotoxy(x, y - 1);
                cout << " ";
                y--;
                gotoxy(x, y);
                cout << body;
                gotoxy(x, y - 1);
                cout << head;
            }
            break;
        case 'a':
            if (x > 2)
            {
                gotoxy(x, y);
                cout << " ";
                gotoxy(x, y - 1);
                cout << " ";
                x--;
                gotoxy(x, y);
                cout << body;
                gotoxy(x, y - 1);
                cout << head;
            }
            break;
        case 's':
            
            if (y < ConsoleHeight - 2)
            {
                gotoxy(x, y);
                cout << " ";
                gotoxy(x, y - 1);
                cout << " ";
                y++;
                gotoxy(x, y);
                cout << body;
                gotoxy(x, y - 1);
                cout << head;
            }
            break;
        case 'd':
            if (x < ConsoleWidth - 2)
            {
                gotoxy(x, y);
                cout << " ";
                gotoxy(x, y - 1);
                cout << " ";
                x++;
                gotoxy(x, y);
                cout << body;
                gotoxy(x, y - 1);
                cout << head;
            }
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
