#include "INGAME.h"
using namespace std;

int main()
{
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    hidecursor();
    inGame a;
    a.loadGame(10);
    system("pause");
    return 0;
}