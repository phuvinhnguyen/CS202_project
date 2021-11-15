#ifndef PLAYER
#define PLAYER

#include "header.h"
using namespace std;

class player
{
private:
    /* data */
    int x, y;
    char head, body;

public:
    player(int x = 50, int y = 40, char head = 'O', char body = 'X') : x(x), y(y), head(head), body(body)
    {
        gotoxy(x, y);
        cout << body;
        gotoxy(x, y - 1);
        cout << head;
    }

    // hàm điều khiển người chơi
    // cập nhật vị trí ng chơi
    char run()
    {
        if (kbhit())
        {
            char a = getch();
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
                if (y < ConsoleHeight)
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
                if (x < ConsoleWidth)
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
    OXY position()
    {
        return OXY(x, y);
    }
};

#endif