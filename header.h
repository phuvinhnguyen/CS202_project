#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

// DEFINE ALL THE MAIN CLASS

struct OXY
{
    int x, y;
    OXY(int x, int y) : x(x), y(y) {}
};

// cây để lưu vị trí các điểm đã bị vật chiếm
// các điểm có trong cây nếu player chạm phải = die
class Tree // vinh
{
    void insert(OXY);
    void remove(OXY);
    bool exist(OXY);
};

class animalLane // hoàng
{
private:
    /* data */
public:
    animalLane(Tree &t, int line, int level);
    ~animalLane();

    // tạo ra 1 lane có động vật chạy qua lại
    // lane ở dòng thứ line, độ khó là level, lưu data vào t
    // hàm được gọi lại nhiều lần, mỗi lần sẽ cập nhật vị trí khác nhau
    // nên có tầm 3,4 loại động vật-
    void run(OXY playerPos, int line);
};

class carLane // nhân
{
private:
    /* data */
public:
    carLane(Tree &t, int line, int level);
    ~carLane();

    // tạo ra 1 lane có xe chạy qua lại
    // lane ở dòng thứ line, độ khó là level, lưu data vào t
    // hàm được gọi lại nhiều lần, mỗi lần sẽ cập nhật vị trí khác nhau
    // nên có tầm 3,4 kiểu xe-
    // nhớ có đèn giao thông
    void run(OXY playerPos, int line);
};

class player // vinh
{
private:
    /* data */
public:
    player();
    ~player();

    // hàm điều khiển người chơi
    // cập nhật vị trí ng chơi
    OXY run();

    // cập nhật vị trí người chơi
    OXY position();
};

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
