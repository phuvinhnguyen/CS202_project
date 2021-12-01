#pragma once
#include "const.h"
using namespace std;

struct OXY
{
    int x, y;
    OXY(int x, int y);
    OXY() {}
    bool operator==(OXY& b);
    OXY operator+(OXY b);
};

bool pointAvailable(OXY a);
void gotoxy(int x, int y);
void gotoxy(OXY a);
void FixConsoleWindow();
void SetWindowSize(SHORT width, SHORT height);
void hidecursor();