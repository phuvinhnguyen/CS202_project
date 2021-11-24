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
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <cstring>
#include <thread>
#include <unordered_set>

using namespace std;

#define ConsoleWidth 100
#define ConsoleHeight 100

#define ScreenWidth		80
#define ScreenHeight	40
#define ScreenTop		10
#define ScreenBottom	50
#define ScreenLeft		10
#define ScreenRight		90

// COLOR
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define WHITE   "\033[1;37m"
#define YELLOW  "\033[1;33m"

// LANE
#define SPAWN_DEF_SPEED 3000
#define SPAWN_LVL_SPEED 200

// TRAFFIC LIGHT
#define LIGHT_DEF_SPEED 10000

// PLAYER
#define PLAYER_SPEED 0
#define PLAYER_DEF_POS_X 50
#define PLAYER_DEF_POS_Y 50

// OBSTACLE
#define PIGEON_DEF_SPEED 200
#define PIGEON_LVL_SPEED 10
#define PIGEON_POWER 1
#define PIGEON_SOUND_FILE L".wav"

#define PTERODACTYL_DEF_SPEED 200
#define PTERODACTYL_LVL_SPEED 10
#define PTERODACTYL_POWER 3
#define PTERODACTYL_SOUND_FILE L".wav"

#define PLANE_DEF_SPEED 30
#define PLANE_LVL_SPEED 0
#define PLANE_POWER 6
#define PLANE_SOUND_FILE L".wav"

#define COUGAR_DEF_SPEED 500
#define COUGAR_LVL_SPEED 20
#define COUGAR_POWER 2
#define COUGAR_SOUND_FILE L".wav"

#define CAR_DEF_SPEED 400
#define CAR_LVL_SPEED 20
#define CAR_POWER 4
#define CAR_SOUND_FILE L".wav"

#define CERATOSAURUS_DEF_SPEED 600
#define CERATOSAURUS_LVL_SPEED 30
#define CERATOSAURUS_POWER 5
#define CERATOSAURUS_SOUND_FILE L".wav"

#define OBSTACLE_TYPE 6