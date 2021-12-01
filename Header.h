#ifndef _HEADER_H_
#define _HEADER_H_

#include "Library.h"

class OXY;
class Pixel;

class InGame;
class JurassicRoad;
class Lane;

class Character;
class Player;
class Obstacle;
class Pigeon;
class Cougar;
class Pteradactyl;
class Car;
class Ceratosaurus;
class Plane;

class OXY {
private:
public:
    int x, y;

    OXY(int x, int y);
    OXY(pair <int, int> A);

    bool invalid() const;
    bool operator==(OXY b);
    OXY operator+(OXY b);
};

class Pixel {
public:
    OXY coord;
    char c;
    const char* color;

    Pixel(OXY _coord, char _c, const char* _color);
    Pixel operator+(OXY& other);
    friend ostream& operator<<(ostream& os, const Pixel& pixel);
};

class TrafficLight {
private:
    OXY anchor;
    int state;  // 0 green, 1 yellow, 2 red
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

class Character {
protected:
    OXY anchor;
    vector < Pixel >* pixels;
    int cooldown;
    const int defCooldown;

    void resetCooldown();
public:
    Character(OXY _anchor, vector < Pixel >* _pixels, int _defCooldown);
    virtual ~Character();
    bool checkCollision(Character* other);

    OXY getAnchor();
};

class Player : public Character {
private:
    OXY prevAnchor;
public:
    Player(OXY _anchor);
    ~Player();
    vector < Pixel >* getPixels();
    void run();
    void draw();
    void erase(bool curPos);
};

class Obstacle : public Character {
protected:
    bool goRight;
    const int power;
public:
    Obstacle(OXY _anchor, vector < Pixel >* _pixels, int _power, int _defCooldown, bool _goRight);
    virtual ~Obstacle();

    virtual void speak() = 0;

    int getPower();
    bool isOffScreen();
    bool move();
    void draw();
    void erase(bool curPos);
};

class Pigeon : public Obstacle {
private:
public:
    Pigeon(OXY _anchor, int level, bool _goRight);
    ~Pigeon();
    
    void speak();
};

class Pterodactyl : public Obstacle {
private:
public:
    Pterodactyl(OXY _anchor, int level, bool _goRight);
    ~Pterodactyl();

    void speak();
};

class Plane : public Obstacle {
private:
public:
    Plane(OXY _anchor, int level, bool _goRight);
    ~Plane();

    void speak();
};

class Cougar: public Obstacle {
private:
public:
    Cougar(OXY _anchor, int level, bool _goRight);
    ~Cougar();

    void speak();
};

class Car : public Obstacle {
private:
public:
    Car(OXY _anchor, int level, bool _goRight);
    ~Car();

    void speak();
};

class Ceratosaurus : public Obstacle {
private:
public:
    Ceratosaurus(OXY _anchor, int level, bool _goRight);
    ~Ceratosaurus();

    void speak();
};

class Lane {
protected:
    OXY anchor;
    int laneWidth;
    int cooldown;
    const int defCooldown;

    void drawLane();
public:
    Lane(OXY _anchor, int _laneWidth, int _defCooldown);
    virtual ~Lane();
    virtual void run(int level) = 0;
    virtual bool checkCollision(Player& player) = 0;
};

template<class T>
class SimpleLane : public Lane {
private:
    list < T > obstacles;
    bool goRight;
    TrafficLight* light;

    void spawnObstacle(int level);
    void resetCooldown();
public:
    SimpleLane(OXY _anchor, int _laneWidth, int level);
    ~SimpleLane();

    void run(int level);
    bool checkCollision(Player& player);
};

class ChaoticLane : public Lane {
private:
    list < Obstacle* > obstacles;

    void spawnObstacle(int level, bool& plane);
    void resetCooldown();
public:
    ChaoticLane(OXY _anchor, int _laneWidth, int level);
    ~ChaoticLane();

    void run(int level);
    bool checkCollision(Player& player);
};


class JurassicRoad
{
private:
    int level;
    Player player;
    list < Lane* > lanes;
public:
    JurassicRoad(int _level);
    ~JurassicRoad();
    bool run();
    bool checkWin();
    bool checkDeath();
};

class InGame {
private:
    int32_t score, level;
    JurassicRoad* game;
    void saveFile();
    void loadGame(string filePath = "", bool music = 0);
    void Dead(int x = 0, int y = 0);
    void Win(int x = 0, int y = 0);
    void Score(int num, int x = 0, int y = 0);
    void CantLoadFile(int x = 0, int y = 0);
public:
    InGame();
    ~InGame();
    // void run();
    void gameplay();
};

void gotoxy(int x, int y);
void gotoxy(OXY coord);
void FixConsoleWindow();
void SetWindowSize(SHORT width, SHORT height);
void playSound(const wchar_t* file);
void changeFont(int W, int H);
// void hidecursor();
void loadPlayer();
void loadObstacles();
void loadTexture(const char* path, vector < Pixel >* g_pixels);


template<class T>
SimpleLane<T>::SimpleLane(OXY _anchor, int _laneWidth, int level)
    : Lane(_anchor, _laneWidth, SPAWN_DEF_SPEED - level * SPAWN_LVL_SPEED), goRight(rand() % 2), light(nullptr) {
    if (rand() % 3 < 2) light = new TrafficLight(anchor);
}

template<class T>
SimpleLane<T>::~SimpleLane() {
    for (auto& obstacle : obstacles) {
        obstacle.erase(true);
    }
    delete light;
}
template<class T>
void SimpleLane<T>::run(int level) {
    if (light) {
        // light->run();
        // if (light->isRed()) return;
    }
    if (cooldown <= 0) {
        spawnObstacle(level);
        resetCooldown();
    }
    else --cooldown;
    for (auto itr = obstacles.begin(); itr != obstacles.end(); ) {
        if (itr->move()) {
            if (itr->isOffScreen()) {
                itr->erase(false);
                auto tmp = itr++;
                obstacles.erase(tmp);
            }
            else {
                itr->draw();
                ++itr;
            }
        }
        else ++itr;
    }
}

template<class T>
void SimpleLane<T>::resetCooldown() {
    cooldown = defCooldown;
}

template<class T>
void SimpleLane<T>::spawnObstacle(int level) {
    obstacles.push_back(T(anchor, level, goRight));
}
template<class T>
bool SimpleLane<T>::checkCollision(Player& player) {
    bool outside = true;
    for (auto& pixel : *player.getPixels()) {
        if ((pixel.coord + player.getAnchor()).y > anchor.y && (pixel.coord + player.getAnchor()).y < anchor.y + laneWidth + 2) {
            outside = false;
            break;
        }
    }
    if (outside) return false;
    for (auto& obstacle : obstacles) {
        if (obstacle.checkCollision(&player)) return true;
    }
    return false;
}



#endif
