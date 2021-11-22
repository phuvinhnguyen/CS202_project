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
};

// cây để lưu vị trí các điểm đã bị vật chiếm
// các điểm có trong cây nếu player chạm phải = die

class Tree
{
private:
    struct node;
    // DATA
    node *head;
    const int MAX = 5;

public:
    Tree();
    void insert(OXY point);
    void remove(OXY point);
    bool exist(OXY point);
};
/*
class animalLane // hoàng
{
private:
public:
    animalLane(Tree &t, int line, int level, int lineNum = 5);
    ~animalLane();

    // tạo ra 1 lane có động vật chạy qua lại
    // lane ở dòng thứ line, độ khó là level, lưu data vào t
    // lane có chiều rộng là lineNum(để mặc định là 5)
    // hàm được gọi lại nhiều lần, mỗi lần sẽ cập nhật vị trí khác nhau
    // nên có tầm 3,4 loại động vật-
    void run();
};

class carLane // nhân
{
private:
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
*/
class player
{
private:
    /* data */
    int x, y;
    char head, body;

public:
    player(int x = 50, int y = 40, char head = 'O', char body = 'X');

    // hàm điều khiển người chơi
    // cập nhật vị trí ng chơi
    char run();

    // cập nhật vị trí người chơi
    OXY position();
};
class inGame
{
private:
    /* data */
public:
    inGame();
    ~inGame();

    // chạy game với độ khó level
    // có save game
    // q để quit game
    // trả về điểm của ng chơi-
    // tự chọn âm thanh, hiệu ứng
    int loadGame(int level, string filePath = "", bool music = 0)
    {
        player plr;
        while (1)
        {
            char input = plr.run();
            if (input == 'q')
                break;
        }
        return 1;
    }
};
/*
// class này tạo menu
// menu gồm điểm của ng chơi
// các nút new game, load game, settings
// setting: bật tắt nhạc, chọn nhân vật, chọn độ khó(hoặc độ khó tăng dần)
class RoadCrossing // quang
{
private:
public:
    RoadCrossing();
    ~RoadCrossing();

    // chạy game đã hoàn thiện(gồm menu)
    void run();
};
*/

// CONSOLE FUNCTION CODE

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
