#include "PLAYER.h"
using namespace std;


void gotoxy_(int x, int y)
{
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void drawPlayer(int x, int y) {
    gotoxy_(x, y);
    cout << "O";
    gotoxy_(x - 1, y + 1);
    cout << "/U\\";
    gotoxy_(x-1, y + 2);
    cout << "/ \\";
}
void erasePlayer(int x, int y) {
    gotoxy_(x, y);
    cout << " ";
    gotoxy_(x - 1, y + 1);
    cout << "   ";
    gotoxy_(x - 1, y + 2);
    cout << "   ";
}

player::player()
{
    x = ix = PLAYER_INIT_X;
    y = iy = PLAYER_INIT_Y;
    drawPlayer(x, y);
}

void player::reset() {
    erasePlayer(x, y);
    x = ix;
    y = iy;
    drawPlayer(x, y);
}

char player::run()
{
    drawPlayer(x, y);

    if (_kbhit())
    {
        char a = _getch();
        switch (a)
        {
        case 'w':
            if (y > 2)
            {
                erasePlayer(x, y);
                y--;
                drawPlayer(x, y);
            }
            break;
        case 'a':
            if (x > 3)
            {
                erasePlayer(x, y);
                x--;
                drawPlayer(x, y);
            }
            break;
        case 's':
            
            if (y < ConsoleHeight - 3)
            {
                erasePlayer(x, y);
                y++;
                drawPlayer(x, y);
            }
            break;
        case 'd':
            if (x < ConsoleWidth - 3)
            {
                erasePlayer(x, y);
                x++;
                drawPlayer(x, y);
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

bool player::collide(Tree<gameObj*> tr) {
    if (tr.exist(OXY(x, y))) return 1;
    if (tr.exist(OXY(x, y + 1))) return 1;
    if (tr.exist(OXY(x + 1, y + 1))) return 1;
    if (tr.exist(OXY(x - 1, y + 1))) return 1;
    if (tr.exist(OXY(x + 1, y + 2))) return 1;
    if (tr.exist(OXY(x - 1, y + 2))) return 1;
    return 0;
}

/*
 O
/|\
/ \
*/
