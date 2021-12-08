#pragma once
#include "EXTRA.h"
using namespace std;

template <class T>
class Tree
{
private:
    T arr2D[ConsoleWidth][ConsoleHeight];
public:
    Tree() {
        for (int i = 0; i < ConsoleWidth; i++) {
            for (int j = 0; j < ConsoleHeight; j++) arr2D[i][j] = 0;
        }
    }
    ~Tree(){}
    void insert(OXY point, T data)
    {
        if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
            arr2D[point.x][point.y] = data;
    }
    void remove(OXY point)
    {
        if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
            arr2D[point.x][point.y] = NULL;
    }
    T exist(OXY point)
    {
        if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
            return arr2D[point.x][point.y];
        return NULL;
    }
};
