#ifndef HEADER
#define HEADER

#include "const.h"
using namespace std;

// FUNCTION ALL CONSOLE FUNCTION

void gotoxy(int x, int y);
void FixConsoleWindow();
void SetWindowSize(SHORT width, SHORT height);

// DEFINE ALL THE MAIN CLASS

struct OXY
{
    int x, y;
    OXY(int x, int y) : x(x), y(y) {}

    bool operator==(OXY &b)
    {
        return (b.x == x) && (b.y == y);
    }
    OXY operator+(OXY b) {
        return OXY(x+b.x, y+b.y);
    }
};

// cây để lưu vị trí các điểm đã bị vật chiếm
// các điểm có trong cây nếu player chạm phải = die
class Tree;

class animalLane;

class carLane // nhân
{
private:
    /* data */
public:
    carLane(Tree &t, int line, int level, int lineNum = 5);
    ~carLane();

    // tạo ra 1 lane có xe chạy qua lại
    // lane ở dòng thứ line, độ khó là level, lưu data vào t
    // lane có chiều rộng là lineNum(để mặc định là 5)
    // hàm được gọi lại nhiều lần, mỗi lần sẽ cập nhật vị trí khác nhau
    // nên có tầm 3,4 kiểu xe-
    // nhớ có đèn giao thông
    void run();
};

class player;

// class này tạo menu
// menu gồm điểm của ng chơi
// các nút new game, load game, settings
// setting: bật tắt nhạc, chọn nhân vật, chọn độ khó(hoặc độ khó tăng dần)
class RoadCrossing // quang
{
private:
    /* data */
public:
    RoadCrossing(/* args */);
    ~RoadCrossing();

    // chạy game đã hoàn thiện(gồm menu)
    void run();
};

// class chạy game
class inGame
{
private:
    /* data */
public:
    inGame(/* args */);
    ~inGame();

    // chạy game với độ khó level
    // có save game
    // q để quit game
    // trả về điểm của ng chơi-
    // tự chọn âm thanh, hiệu ứng
    int loadGame(int level, string filePath = "", bool music = 0);
};

// CONSOLE FUNCTION CODE

void gotoxy(OXY coord)
{
    gotoxy(coord.x, coord.y);
}

void gotoxy(int x, int y)
{
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSize;
    SMALL_RECT WindowSize;

    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Bottom = height - 1;
    WindowSize.Right = width - 1;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
    SetConsoleScreenBufferSize(hStdout, NewSize);
}

#endif
