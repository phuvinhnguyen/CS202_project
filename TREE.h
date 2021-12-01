#pragma once
#include "EXTRA.h"
using namespace std;

class Tree
{
private:
    bool arr2D[ConsoleWidth][ConsoleHeight];
public:
    Tree();
    ~Tree();
    void insert(OXY point);
    void remove(OXY point);
    bool exist(OXY point);
};
