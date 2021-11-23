#include "Header.h"
using namespace std;

Tree::Tree() {
    arr2D = new bool* [ConsoleWidth];
    for (int i = 0; i < ConsoleWidth; i++) {
        arr2D[i] = new bool[ConsoleHeight];
        for (int j = 0; j < ConsoleHeight; j++) arr2D[i][j] = 0;
    }
}
Tree::~Tree() {
    for (int i = 0; i < ConsoleWidth; i++) delete arr2D[i];
    delete[] arr2D;
}
void Tree::insert(OXY point)
{
    if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
        arr2D[point.x][point.y] = 1;
}
void Tree::remove(OXY point)
{
    if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
        arr2D[point.x][point.y] = 0;
}
bool Tree::exist(OXY point)
{
    if (point.x >= 0 && point.x < ConsoleWidth && point.y >= 0 && point.y < ConsoleHeight)
        return arr2D[point.x][point.y];
    return 0;
}
