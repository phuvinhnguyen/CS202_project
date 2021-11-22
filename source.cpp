#include "header.h"
using namespace std;

player::player(int x = 50, int y = 40, char head = 'O', char body = 'X') : x(x), y(y), head(head), body(body)
{
    gotoxy(x, y);
    cout << body;
    gotoxy(x, y - 1);
    cout << head;
}
char player::run()
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
OXY player::position()
{
    return OXY(x, y);
}
struct Tree::node
{
    vector<OXY> data;
    node *upleft, *upright, *downleft, *downright;

    node(OXY ndata)
    {
        data.push_back(ndata);
        upleft = upright = downleft = downright = nullptr;
    }

    node(vector<OXY> ndata)
    {
        data = ndata;
        upleft = upright = downleft = downright = nullptr;
    }

    ~node()
    {
        delete upright;
        delete upleft;
        delete downright;
        delete downleft;
    }
};
Tree::Tree() : head(nullptr) {}
void Tree::insert(OXY point)
{
    if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
        throw("Tree error: insert out of range point");

    if (head == nullptr)
    {
        head = new node(point);
        return;
    }

    node *tm = head;
    OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
    while (tm->upleft != nullptr)
    {
        if (point.x < (upleft.x + downright.x) / 2)
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upleft;
                downright.x -= ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downleft;
                upleft.y += ((downright.y - upleft.y) / 2);
                downright.x -= ((downright.x - upleft.x) / 2);
            }
        }
        else
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upright;
                upleft.x += ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downright;
                upleft.x += ((downright.x - upleft.x) / 2);
                upleft.y += ((downright.y - upleft.y) / 2);
            }
        }
    }

    for (int i = 0; i < tm->data.size(); i++)
    {
        if (point == tm->data[i])
            return;
    }

    if (tm->data.size() < MAX)
    {
        tm->data.push_back(point);
    }
    else
    {
        vector<OXY> upleftnode, uprightnode, downleftnode, downrightnode;
        for (int i = 0; i < tm->data.size(); i++)
        {
            if (point.x < (upleft.x + downright.x) / 2)
            {
                if (point.y < (upleft.y + downright.y) / 2)
                    upleftnode.push_back(tm->data[i]);
                else
                    downleftnode.push_back(tm->data[i]);
            }
            else
            {
                if (point.y < (upleft.y + downright.y) / 2)
                    uprightnode.push_back(tm->data[i]);
                else
                    downrightnode.push_back(tm->data[i]);
            }
        }

        tm->data.clear();
        tm->downleft = new node(downleftnode);
        tm->downright = new node(downrightnode);
        tm->upleft = new node(upleftnode);
        tm->upright = new node(uprightnode);
    }
}
void Tree::remove(OXY point)
{
    if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
        return;

    node *tm = head;
    OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
    while (tm->upleft != nullptr)
    {
        if (point.x < (upleft.x + downright.x) / 2)
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upleft;
                downright.x -= ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downleft;
                upleft.y += ((downright.y - upleft.y) / 2);
                downright.x -= ((downright.x - upleft.x) / 2);
            }
        }
        else
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upright;
                upleft.x += ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downright;
                upleft.x += ((downright.x - upleft.x) / 2);
                upleft.y += ((downright.y - upleft.y) / 2);
            }
        }
    }

    for (int i = 0; i < tm->data.size(); i++)
    {
        if (point == tm->data[i])
        {
            tm->data.erase(tm->data.begin() + i);
            return;
        }
    }
}
bool Tree::exist(OXY point)
{
    if (point.x < 0 || point.x > ConsoleWidth || point.y < 0 || point.y > ConsoleHeight)
        return 0;

    node *tm = head;
    OXY upleft(0, 0), downright(ConsoleWidth, ConsoleHeight);
    while (tm->upleft != nullptr)
    {
        if (point.x < (upleft.x + downright.x) / 2)
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upleft;
                downright.x -= ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downleft;
                upleft.y += ((downright.y - upleft.y) / 2);
                downright.x -= ((downright.x - upleft.x) / 2);
            }
        }
        else
        {
            if (point.y < (upleft.y + downright.y) / 2)
            {
                tm = tm->upright;
                upleft.x += ((downright.x - upleft.x) / 2);
                downright.y -= ((downright.y - upleft.y) / 2);
            }
            else
            {
                tm = tm->downright;
                upleft.x += ((downright.x - upleft.x) / 2);
                upleft.y += ((downright.y - upleft.y) / 2);
            }
        }
    }

    for (int i = 0; i < tm->data.size(); i++)
    {
        if (point == tm->data[i])
            return true;
    }
    return false;
}
void gotoxy(int x, int y)
{
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}
void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSize;
    SMALL_RECT WindowSize;

    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Bottom = height - 1;
    WindowSize.Right = width - 1;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
    SetConsoleScreenBufferSize(hStdout, NewSize);
}
