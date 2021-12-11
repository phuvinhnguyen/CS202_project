#ifndef _HEADER_H_
#define _HEADER_H_

#include "Library.h"

class OXY
{
private:
public:
    int x, y;

    OXY(int x, int y);
    OXY(pair<int, int> A);

    bool invalid() const;
    bool operator==(OXY b);
    OXY operator+(OXY b);
};

class Pixel
{
public:
    OXY coord;
    char c;
    string color;

    Pixel(OXY _coord, char _c, const char *_color);
    Pixel(OXY _coord, char _c, string _color);
    Pixel operator+(OXY &other);
    friend ostream &operator<<(ostream &os, const Pixel &pixel);
};

class TrafficLight
{
private:
    OXY anchor;
    int state; // 0 green, 1 yellow, 2 red
    int cooldown;
    const int defCooldown;

    void resetCooldown();
    void switchLight();
    void draw();

public:
    TrafficLight(OXY _anchor);
    ~TrafficLight();
    bool isRed();
    void run();
};

class Character
{
protected:
    OXY anchor;
    vector<Pixel> *pixels;
    int cooldown;
    const int defCooldown;

    void resetCooldown();

public:
    Character(OXY _anchor, vector<Pixel> *_pixels, int _defCooldown);
    virtual ~Character();
    bool checkCollision(Character *other);

    OXY getAnchor();
};

class Player : public Character
{
private:
    OXY prevAnchor;

public:
    Player(OXY _anchor);
    ~Player();
    vector<Pixel> *getPixels();
    bool run();
    void draw();
    void erase(bool curPos);
    void setDefPos(OXY _anchor);
};

class Obstacle : public Character
{
protected:
    bool isMoving;
    bool goRight;
    const int power;

public:
    Obstacle(OXY _anchor, vector<Pixel> *_pixels, int _power, int _defCooldown, bool _goRight);
    virtual ~Obstacle();

    virtual void setMove(bool move);
    virtual void speak() = 0;

    int getPower();
    bool isOffScreen();
    bool move();
    void draw();
    void erase(bool curPos);
};

class Pigeon : public Obstacle
{
private:
public:
    Pigeon(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Pigeon();

    void speak();
};

class Pterodactyl : public Obstacle
{
private:
public:
    Pterodactyl(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Pterodactyl();

    void speak();
};

class Plane : public Obstacle
{
private:
public:
    Plane(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Plane();

    void speak();
};

class Cougar : public Obstacle
{
private:
public:
    Cougar(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Cougar();

    void speak();
};

class Car : public Obstacle
{
private:
public:
    Car(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Car();

    void speak();
    void setMove(bool move);
};

class Ceratosaurus : public Obstacle
{
private:
public:
    Ceratosaurus(OXY _anchor, int level, bool _goRight, int laneWidth);
    ~Ceratosaurus();

    void speak();
};

class Lane
{
protected:
    OXY anchor;
    int laneWidth;
    int cooldown;
    const int defCooldown;
    TrafficLight *light;

    void drawLane(bool lastLane);

public:
    Lane(OXY _anchor, int _laneWidth, int _defCooldown, bool hasLight, bool lastLane);

    virtual ~Lane();
    virtual void run(int level) = 0;
    virtual bool checkCollision(Player &player) = 0;
    virtual void resumeLane(bool lastLane) = 0;
};

template <class T>
class SimpleLane : public Lane
{
private:
    list<T> obstacles;
    bool goRight;

    bool spawnObstacle(int level);
    void resetCooldown();
    void changeLight();

public:
    SimpleLane(OXY _anchor, int _laneWidth, int level, bool hasLight, bool lastLane);
    ~SimpleLane();

    void run(int level);
    bool checkCollision(Player &player);
    void resumeLane(bool lastLane);
};

class ChaoticLane : public Lane
{
private:
    list<Obstacle *> obstacles;

    void spawnObstacle(int level, bool &plane);
    void resetCooldown();
    void changeLight();

public:
    ChaoticLane(OXY _anchor, int _laneWidth, int level, bool hasLight, bool lastLane);
    ~ChaoticLane();

    void run(int level);
    bool checkCollision(Player &player);
    void resumeLane(bool lastLane);
};

class InGame;

class JurassicRoad
{
private:
    int difficulty;
    int level;
    Player player;
    list<Lane *> lanes;
    InGame *ingame;

public:
    JurassicRoad(int _level, int _difficulty, InGame *_ingame);
    ~JurassicRoad();
    int run();
    bool checkWin();
    bool checkDeath();
    void resume();
};

class InGame {
private:
    string username;
    int32_t score, maxlevel, level, difficulty, endless_lvl;
    JurassicRoad *game;
    void gameTitle(int x, int y);

    bool startMenu(int x, int y);
    bool playMenu(int x, int y);
    bool gameMenu(int x, int y);
    bool loadMenu(int x, int y);
    bool saveMenu(int x, int y);
    bool instructionMenu(int x, int y);
    bool difficultyMenu(int x, int y);
    int menu(int x, int y, vector<string> &options, string menu_name);

    bool settingsMenu(int x, int y);

    void readTitle(string dir, int x, int y);
    string linkBoard(int x, int y);
    void saveFile(int x = 5, int y = 15);
    bool loadGame(string filePath = "", bool music = 0);
    void CantLoadFile(int x = 0, int y = 0);

    bool Dead(int x = 0, int y = 0);
    bool Win(int x = 0, int y = 0);
    void Score(int num, int x = 0, int y = 0);

public:
    InGame();
    ~InGame();
    void run();
    void gameplay(int x, int y);

    int pauseMenu(int x, int y);
    bool hasSound;
};

void gotoxy(int x, int y);
void gotoxy(OXY coord);
void FixConsoleWindow();
void SetWindowSize(SHORT width, SHORT height);
void playSound(const wchar_t *file);
void changeFont(int W, int H);
// void hidecursor();
void loadCharacters();
void loadTexture(const char *path, vector<Pixel> *g_pixels, const char *color);

template <class T>
SimpleLane<T>::SimpleLane(OXY _anchor, int _laneWidth, int level, bool hasLight, bool lastLane)
    : Lane(_anchor, _laneWidth, 6 * (SPAWN_DEF_SPEED - level * SPAWN_LVL_SPEED), hasLight, lastLane), goRight(rand() % 2)
{
}

template <class T>
SimpleLane<T>::~SimpleLane()
{
    for (auto &obstacle : obstacles)
    {
        obstacle.erase(true);
    }
    delete light;
}
template <class T>
void SimpleLane<T>::run(int level)
{
    if (light)
    {
        light->run();
        changeLight();
    }
    if (cooldown <= 0 && (!light || (light && !light->isRed())))
    {
        if (spawnObstacle(level)) resetCooldown();
    }
    else
        --cooldown;
    for (auto itr = obstacles.begin(); itr != obstacles.end();)
    {
        if (itr->move())
        {
            if (itr->isOffScreen())
            {
                itr->erase(false);
                auto tmp = itr++;
                obstacles.erase(tmp);
            }
            else
            {
                itr->erase(false);
                itr->draw();
                ++itr;
            }
        }
        else
            ++itr;
    }
}

template <class T>
void SimpleLane<T>::changeLight()
{
    for (T &obstacle : obstacles)
    {
        obstacle.setMove(!light->isRed());
    }
}

template <class T>
void SimpleLane<T>::resetCooldown()
{
    cooldown = defCooldown;
}

template <class T>
void SimpleLane<T>::resumeLane(bool lastLane)
{
    drawLane(lastLane);
    for (auto &obstacle : obstacles)
    {
        obstacle.draw();
    }
}

template <class T>
bool SimpleLane<T>::spawnObstacle(int level)
{
    T obstacle(anchor, level, goRight, laneWidth);
    if (obstacles.empty()) {
        obstacles.push_back(obstacle);
        return true;
    }
    else {
        Character* thisObstacle = &obstacle;
        Character* thatObstacle = &obstacles.back();
        if (thisObstacle->checkCollision(thatObstacle)) return false;
        obstacles.push_back(obstacle);
        return true;
    }
}
template <class T>
bool SimpleLane<T>::checkCollision(Player &player)
{
    bool outside = true;
    for (auto &pixel : *player.getPixels())
    {
        if ((pixel.coord + player.getAnchor()).y > anchor.y && (pixel.coord + player.getAnchor()).y < anchor.y + laneWidth + 2)
        {
            outside = false;
            break;
        }
    }
    if (outside)
        return false;
    for (auto &obstacle : obstacles)
    {
        if (obstacle.checkCollision(&player))
            return true;
    }
    return false;
}

#endif