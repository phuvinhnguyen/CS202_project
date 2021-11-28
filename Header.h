#ifndef HEADER
#define HEADER

#include "const.h"
using namespace std;

// FUNCTION ALL CONSOLE FUNCTION

void gotoxy(int x, int y);
void FixConsoleWindow();
void SetWindowSize(SHORT width, SHORT height);
void hidecursor();

// DEFINE ALL THE MAIN CLASS

class land {
public:
    virtual void run() = 0;
    virtual ~land() {};
};

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

class Tree
{
private:
    bool** arr2D;
public:
    Tree();
    ~Tree();
    void insert(OXY point);
    void remove(OXY point);
    bool exist(OXY point);
};

class AnimalLane : public land;

class carLane : public land// nhân
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

class player
{
private:
    int x, y, ix, iy;
    char head, body;

public:
    player(int x = 50, int y = 40, char head = 'O', char body = 'X');
    void reset();
    char run();
    OXY position();
};
class inGame
{
private:
    int32_t score, level_;
    vector<char> land_;
    void saveFile(int x = 0, int y = 0);
    bool loadFile(string dir);
    void Dead(int x = 0, int y = 0);
    void Win(int x = 0, int y = 0);
    void Score(int num, int x = 0, int y = 0);
    void newData();
public:
    inGame();
    ~inGame();
    void loadGame(int level, string filePath = "", bool music = 0);
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

#endif
