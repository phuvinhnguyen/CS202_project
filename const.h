#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <random>
#include <ctime>
#include <mmsystem.h>

#define ConsoleWidth 100
#define ConsoleHeight 48


// For Animal
#define DEFAULT_SPAWN_SPEED 60
#define DEFAULT_MOVE_SPEED 60
#define LEVEL_SPAWN_SPEED 5
#define LEVEL_MOVE_SPEED 5
#define PIGEON_SOUND_FILE ""
#define PTERODACTYL_SOUND_FILE ""
#define DOG_SOUND_FILE ""
#define DINO_SOUND_FILE ""
#define ANIMAL_TYPE 4
string g_laneline = string('_', ConsoleWidth);
vector < OXY > g_pigeonpixel = { };
vector < OXY > g_pterodactylpixel = { };
vector < OXY > g_dogpixel = { };
vector < OXY > g_dinopixel = { };