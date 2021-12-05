#pragma once
#include "INGAME.h"
using namespace std;

class menu {
	static void gameTitle(int x, int y);
	static int button(int x, int y);
	static string linkBoard(int x, int y);
public:
	static void run();
};