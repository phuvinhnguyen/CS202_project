#ifndef ANIMAL
#define ANIMAL

#include "header.h"

class AnimalLane { // Hoàng
private:
    list < Animal* > animals;
    OXY anchor;
    Tree* t;
    int laneNumber;
    int level;
    int laneWidth;
    int spawnCooldown;
    int moveCooldown;
    bool goRight;
    static string lane;

    void spawnAnimal();
    void drawLane();
    bool checkCollision(player& A);
    void resetSpawn();
    void resetMove();
public:
    AnimalLane(Tree& _t, int _laneNumber, int _level, int _laneWidth = 5);
    ~AnimalLane();
    // tạo ra 1 lane có động vật chạy qua lại
    // lane ở dòng thứ line, độ khó là level, lưu data vào t
    // lane có chiều rộng là lineNum(để mặc định là 5)
    // hàm được gọi lại nhiều lần, mỗi lần sẽ cập nhật vị trí khác nhau
    // nên có tầm 3,4 loại động vật
    bool run();
};

class Animal {
protected:
    OXY anchor;
    vector < OXY >* pixels;
public:
    Animal(OXY& _anchor) : Animal(_anchor) { };
    virtual ~Animal() { };
    virtual void speak() = 0;
    void draw();
    void playsound(string file);
    void move(bool goRight);
    bool checkCollision(OXY other);
    OXY getPos();
};

class Pigeon : public Animal {
private:
public:
    Pigeon(OXY& _anchor) : Animal(_anchor), pixels(&g_pigeonpixel) { };
    ~Pigeon() { };
    void speak();
};

class Dog : public Animal {
private:
public:
    Dog(OXY& _anchor) : Animal(_anchor), pixels(&g_dogpixel) { };
    ~Dog() { };
    void speak();
};

class Pterodactyl : public Animal {
private:
public:
    Pterodactyl(OXY& _anchor) : Animal(_anchor), pixels(&g_pterodactylpixel) { };
    ~Pterodactyl() { };
    void speak();
}

class Dino : public Animal {
private:
public:
    Dino(OXY& _anchor) : Animal(_anchor), pixels(&g_dinopixel) { };
    ~Dino() { };
    void speak();
};

#endif