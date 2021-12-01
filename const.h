#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <mmsystem.h>
using namespace std;


#define ConsoleWidth 100
#define ConsoleHeight 48
const LPCTSTR WIN_SOUND_FILE = TEXT("win.wav");
const LPCTSTR LOSE_SOUND_FILE = TEXT("lose.wav");
const LPCTSTR PIGEON_SOUND_FILE = TEXT("pigeon.wav");
const LPCTSTR DOG_SOUND_FILE = TEXT("dog.wav");
const LPCTSTR DINO_SOUND_FILE = TEXT("dino.wav");
const LPCTSTR PTERODACTYL_SOUND_FILE = TEXT("pterodactyl.wav");
#define DEFAULT_SPAWN_SPEED 8000
#define DEFAULT_MOVE_SPEED 120
#define LEVEL_SPAWN_SPEED -75
#define LEVEL_MOVE_SPEED -3
#define RANDOM_MOVE_SPEED 200
#define RANDOM_SPAWN_SPEED 500
#define GREEN_LIGHT_TIME 15000
#define RED_LIGHT_TIME 10000
#define RAND_LIGHT_TIME 500
#define ANIMAL_TYPE 4
#define MAX_LANE_NUM 4 //EXTRA LANE NUM
#define MIN_LANE_NUM 4
#define _X_INIT_LEFT 15
#define _X_INIT_RANGE 30
#define INITIAL_OBJECT_NUM 5