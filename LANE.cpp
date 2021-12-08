#include "LANE.h"
using namespace std;


land::land(Tree<gameObj*>* _t, int _laneLine, int _level, int _laneWidth, bool _right, bool _carLane, int trafficLightPos, int red, int green) :
	laneLine(_laneLine), laneWidth(_laneWidth), level(_level), goRight(_right), count(DEFAULT_SPAWN_SPEED) {
	tr = _t;
	if (_carLane) carLane = ANIMAL_TYPE;
	else carLane = 0;
	countSpawnLoop = DEFAULT_SPAWN_SPEED + level * LEVEL_SPAWN_SPEED;
	x_init = (goRight ? -1 : ConsoleWidth + 1);
	x_stop_line = trafficLightPos;
	redlight_time = red;
	greenlight_time = green;
	timer = 0;
}
bool land::trafficLight() {
	timer++;

	if (timer > (redlight_time + greenlight_time)) {
		timer = 0;
		if (pointAvailable(OXY(x_stop_line - !goRight, laneLine)))
		{
			gotoxy(x_stop_line - !goRight, laneLine);
			cout << "G";
		}
		return 1;
	}
	else if (timer > greenlight_time) {
		if (pointAvailable(OXY(x_stop_line - !goRight, laneLine)))
		{
			gotoxy(x_stop_line - !goRight, laneLine);
			cout << "R";
		}
		return 0;
	}
	else {
		if (pointAvailable(OXY(x_stop_line - !goRight, laneLine)))
		{
			gotoxy(x_stop_line - !goRight, laneLine);
			cout << "G";
		}
		return 1;
	}
}
void land::run(bool soundOn){
	for (int i = 0; i < __GAMEOBJ__.size(); i++) {
		if (__GAMEOBJ__[i]->dead()) {
			delete __GAMEOBJ__[i];
			__GAMEOBJ__.erase(__GAMEOBJ__.begin() + i);
		}
		else if (!(carLane && !trafficLight()
			&& __GAMEOBJ__[i]->getPos().x == x_stop_line 
			&& __GAMEOBJ__[i]->getMoral()))
			__GAMEOBJ__[i]->move();
	}

	count++;
	if (count > countSpawnLoop + rand() % RANDOM_SPAWN_SPEED) {
		count = 0;
		Spawn();
	}
}
void land::Spawn(int x) {
	if (x == -1) x = x_init;
	//int y_init = rand() % (laneWidth - 2);
	switch (rand() % ANIMAL_TYPE + carLane) {
	case 0:
		__GAMEOBJ__.push_back(new dog(tr, level, OXY(x, laneLine + rand() % (laneWidth - dog_high)), goRight));
		break;
	case 1:
		__GAMEOBJ__.push_back(new pigeon(tr, level, OXY(x, laneLine + rand() % (laneWidth - pigeon_high)), goRight));
		break;
	case 2:
		__GAMEOBJ__.push_back(new dino(tr, level, OXY(x, laneLine + rand() % (laneWidth - dino_high)), goRight));
		break;
	case 3:
		__GAMEOBJ__.push_back(new pterodactyl(tr, level, OXY(x, laneLine + rand() % (laneWidth - pterodactyl_high)), goRight));
		break;
	case 4:
		__GAMEOBJ__.push_back(new car(tr, level, OXY(x, laneLine + rand() % (laneWidth - car_high)), goRight));
		break;
	case 5:
		__GAMEOBJ__.push_back(new truck(tr, level, OXY(x, laneLine + rand() % (laneWidth - truck_high)), goRight));
		break;
	case 6:
		__GAMEOBJ__.push_back(new alien(tr, level, OXY(x, laneLine + rand() % (laneWidth - alien_high)), goRight));
		break;
	case 7:
		__GAMEOBJ__.push_back(new bike(tr, level, OXY(x, laneLine + rand() % (laneWidth - bike_high)), goRight));
		break;
	}
}
land::~land() {
	for (int i = 0; i < __GAMEOBJ__.size(); i++) delete __GAMEOBJ__[i];
	__GAMEOBJ__.clear();
}
void land::init() {
	int init_obj = rand() % (level > 5 ? 5 : level) + INITIAL_OBJECT_NUM;
	for (int i = 0; i < init_obj; i++)
		Spawn(rand() % (ConsoleWidth - 16) + 8);
}
