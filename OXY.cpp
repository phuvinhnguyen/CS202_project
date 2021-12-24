#include "Header.h"

OXY::OXY(int x, int y) : x(x), y(y) { }

OXY::OXY(pair <int, int> A) : x(A.first), y(A.second) { }

bool OXY::invalid() const {
    return x < ScreenLeft || x >= ScreenRight || y < ScreenTop || y >= ScreenBottom;
}

bool OXY::operator==(OXY b){
    return (b.x == x) && (b.y == y);
}

OXY OXY::operator+(OXY b) { 
    return OXY(x+b.x, y+b.y);
}