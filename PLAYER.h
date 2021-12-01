#pragma once
#include "EXTRA.h"
using namespace std;

class player
{
private:
    int x, y, ix, iy;
    char head, body;

public:
    player(int x = 50, int y = 40, char head = 'O', char body = 'X');
    void reset();
    char run();
    OXY position();
};