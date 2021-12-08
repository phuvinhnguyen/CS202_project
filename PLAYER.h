#pragma once
#include "EXTRA.h"
#include "TREE.h"
#include "LANE.h"
using namespace std;

class player
{
private:
    int x, y, ix, iy;

public:
    player();
    void reset();
    char run();
    OXY position();
    bool collide(Tree<gameObj*> tr);
};