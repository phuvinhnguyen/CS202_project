#pragma once
#include "TREE.h"
using namespace std;

#define dog_high 1
#define dino_high 1
#define pigeon_high 1
#define pterodactyl_high 1
#define car_high 1
#define truck_high 1
#define alien_high 1
#define bike_high 1

class gameObj {
protected:
    vector<OXY> pixels_head, pixels_tail, pixels_body;
    OXY pos, mov_vec;
    Tree<gameObj*>* tr;
    bool alive, goRight, moral;
    int COUNTLOOP, count, priority;
public:
    gameObj(Tree<gameObj*>* _t, OXY init, bool _goRight, int _level);
    void move();
    bool dead() { return !alive; }
    OXY getPos() { return pos; }
    bool getMoral() { return moral; }
    virtual void speak() = 0;
    void rm();
    virtual void draw(OXY a) = 0;
    virtual ~gameObj();
};

class dog : public gameObj
{
public:
    dog(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~dog();
};

class dino : public gameObj
{
public:
    dino(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~dino();
};

class pigeon : public gameObj
{
public:
    pigeon(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~pigeon();
};

class pterodactyl : public gameObj
{
public:
    pterodactyl(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~pterodactyl();
};


class car : public gameObj
{
public:
    car(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~car();
};

class truck : public gameObj
{
public:
    truck(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~truck();
};

class alien : public gameObj
{
public:
    alien(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~alien();
};

class bike : public gameObj
{
public:
    bike(Tree<gameObj*>* _t, int level, OXY init, bool _goRight);
    void speak();
    void draw(OXY a);
    ~bike();
};

class land {
    Tree<gameObj*>* tr;
    int level, laneWidth, countSpawnLoop, laneLine, count, carLane;
    bool goRight;
    int x_init, x_stop_line, redlight_time, timer, greenlight_time;
    vector<gameObj*> __GAMEOBJ__;

    void Spawn(int x = -1);
    bool trafficLight();
public:
    void init();
    land(Tree<gameObj*>* _t, int laneLine, int _level = 0, int _landWidth = 5, bool _right = 0, bool _carLane = 1, int trafficLightPos = -100, int red = 10, int green = 10);
    void run(bool soundOn);
    ~land();
};

