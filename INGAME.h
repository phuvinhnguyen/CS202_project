#pragma once
#include "TREE.h"
#include "PLAYER.h"
#include "LANE.h"
using namespace std;

struct laneData {
    bool carLane, goRight;
    int red, green, x_init;
    laneData(){}
    laneData(bool _carLane, bool _goRight, int _red = 0, int _green = 0, int x_init = -1):carLane(_carLane), goRight(_goRight), red(_red), green(_green), x_init(x_init){}
};

class inGame
{
private:
    int32_t SCORE, LEVEL;
    vector<laneData> LANE_DATA;
    bool SOUND;
    void saveFile(int x = 0, int y = 0);
    bool loadFile(string dir);
    void Dead(int x = 0, int y = 0);
    void Win(int x = 0, int y = 0);
    void Score(int x = 0, int y = 0);
    bool options(char a);
    void newData();
public:
    inGame();
    ~inGame();
    void loadGame(int level, string filePath = "", bool music = 0);
};