#include "Header.h"

int background[ConsoleWidth][ConsoleHeight];

Pixel::Pixel(OXY _coord, char _c, const char* _color) : coord(_coord), c(_c), color(_color) {

}

Pixel::Pixel(OXY _coord, char _c, string _color) : coord(_coord), c(_c), color(_color) {

}

Pixel Pixel::operator+(OXY& other) {
	return Pixel(coord + other, c, color);
}

ostream& operator<<(ostream& os, const Pixel& pixel) {
	if (pixel.coord.invalid()) return os;
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(pixel.coord);
	SetConsoleTextAttribute(console_color, background[pixel.coord.x][pixel.coord.y]);
	os << pixel.color << pixel.c;
	return os;
}