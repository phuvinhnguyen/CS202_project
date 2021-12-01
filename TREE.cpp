#include "TREE.h"
using namespace std;

Tree::Tree() {
    for (int i = 0; i < ConsoleWidth; i++) {
        for (int j = 0; j < ConsoleHeight; j++) arr2D[i][j] = 0;
    }
}
Tree::~Tree() {}
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
        return arr2D[point.x][point.y] == true;
    return 0;
}
