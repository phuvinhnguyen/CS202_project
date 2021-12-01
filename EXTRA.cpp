#include "EXTRA.h"
using namespace std;

bool pointAvailable(OXY a) {
    if (a.x >= 0 && a.x < ConsoleWidth - 1 && a.y >= 0 && a.y < ConsoleHeight - 1) return true;
    return false;
}

void gotoxy(int x, int y)
{
    if (!pointAvailable(OXY(x, y))) return;
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void gotoxy(OXY a) {
    gotoxy(a.x, a.y);
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

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


OXY::OXY(int x, int y) : x(x), y(y) {}

bool OXY::operator==(OXY& b)
{
    return (b.x == x) && (b.y == y);
}

OXY OXY::operator+(OXY b) {
    return OXY(x + b.x, y + b.y);
}