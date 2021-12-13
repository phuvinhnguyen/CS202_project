#include "Header.h"

string g_laneline(ScreenWidth, '_');
extern int background[ConsoleWidth][ConsoleHeight];

Lane::Lane(OXY _anchor, int _laneWidth, int _defCooldown, bool hasLight, bool lastLane) :
	anchor(_anchor), laneWidth(_laneWidth), defCooldown(_defCooldown) {
	if (hasLight) light = new TrafficLight(anchor);
	else light = nullptr;
	drawLane(lastLane);                             
};

Lane::~Lane() { }                    
void Lane::drawLane(bool lastLane) {
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(anchor);                                       
	for (int i = 0; i < ScreenWidth; ++i) {
		if (background[anchor.x + i][anchor.y]) break;
		SetConsoleTextAttribute(console_color, 42);
		background[anchor.x + i][anchor.y] = 42;
		cout << ' ';
	}
	gotoxy(anchor.x, anchor.y + laneWidth + 2);
	if (lastLane) {
		for (int i = 0; i < ScreenWidth; ++i) {
			SetConsoleTextAttribute(console_color, 42);
			background[anchor.x + i][anchor.y + laneWidth + 2] = 42;
			cout << ' ';
		}
	}
	else {
		for (int i = 0; i < ScreenWidth; ++i) {
			int color = 1;
			if (i % 6 < 3) color = 113;
			SetConsoleTextAttribute(console_color, color);
			background[anchor.x + i][anchor.y + laneWidth + 2] = color;
			cout << ' ';
		}
	}
	SetConsoleTextAttribute(console_color, 15);
}

ChaoticLane::ChaoticLane(OXY _anchor, int _laneWidth, int level, bool hasLight, bool lastLane)
	: Lane(_anchor, _laneWidth, SPAWN_DEF_SPEED - level * SPAWN_LVL_SPEED, hasLight, lastLane) { }

ChaoticLane::~ChaoticLane() {
	for (auto& obstacle : obstacles) {
		obstacle->erase(true);
		delete obstacle;
	}
}
void ChaoticLane::resumeLane(bool lastLane) {
	drawLane(lastLane);
	for (auto& obstacle : obstacles) {
		obstacle->draw();
	}
}
void ChaoticLane::changeLight() {
	for (auto& obstacle : obstacles) {
		obstacle->setMove(!light->isRed());
	}
}

void ChaoticLane::resetCooldown() {
	cooldown = defCooldown - rand() % 20;
	if (cooldown < 0) cooldown = 0;
}
void ChaoticLane::run(int level) {
	if (light) {
		light->run();
		changeLight();
	}
	if (cooldown <= 0) {
		bool plane = false;
		spawnObstacle(level, plane);
		resetCooldown();
		if (plane) cooldown += 100;
	}
	else --cooldown;
	set < Obstacle* > movedObst;
	for (auto i = obstacles.begin(); i != obstacles.end(); ) {
		if ((*i)->move()) {
			movedObst.insert(*i);
			for (auto j = obstacles.begin(); j != obstacles.end(); ) {
				if (i == j) {
					j++;
					continue;
				}
				if ((*i)->checkCollision(*j)) {
					int p1 = (*i)->getPower();
					int p2 = (*j)->getPower();
					if (p1 == p2) {
						Obstacle* a = *i;
						Obstacle* b = *j;
						auto tmp = i++;
						if (i == j) i++;
						a->erase(!movedObst.count(a));
						b->erase(!movedObst.count(b));
						delete a;
						delete b;
						obstacles.erase(tmp);
						obstacles.erase(j);
						break;
					}
					else if (p1 < p2) {
						Obstacle* a = *i;
						auto tmp = i++;
						a->erase(!movedObst.count(a));
						delete a;
						obstacles.erase(tmp);
						break;
					}
					else {
						Obstacle* b = *j;
						auto tmp = j++;
						b->erase(!movedObst.count(b));
						delete b;
						obstacles.erase(tmp);
					}
				}
				else ++j;
			}
		}
		else ++i;
	}
	for (auto itr = obstacles.begin(); itr != obstacles.end(); ) {
		if ((*itr)->isOffScreen()) {
			auto tmp = itr++;
			Obstacle* wtf = *tmp;
			wtf->erase(false);
			delete wtf;
			obstacles.erase(tmp);
		}
		else ++itr;
	}
	for (auto& obstacle : obstacles) {
		if (movedObst.count(obstacle)) {
			obstacle->erase(false);
			obstacle->draw();
		}
	}
}

void ChaoticLane::spawnObstacle(int level, bool& plane) {
	int obstacle_type = rand() % 100 + 1;
	Obstacle* obstacle = nullptr;
	int goRight = rand() % 2;
	plane = false;
	if (obstacle_type > 98)			obstacle = new Plane(anchor, level, goRight, laneWidth), plane = true;
	else if (obstacle_type > 85)	obstacle = new Ceratosaurus(anchor, level, goRight, laneWidth);
	else if (obstacle_type > 70)	obstacle = new Car(anchor, level, goRight, laneWidth);
	else if (obstacle_type > 50)	obstacle = new Pterodactyl(anchor, level, goRight, laneWidth);
	else if (obstacle_type > 30)	obstacle = new Cougar(anchor, level, goRight, laneWidth);
	else							obstacle = new Pigeon(anchor, level, goRight, laneWidth);
	obstacles.push_back(obstacle);
}

bool ChaoticLane::checkCollision(Player& player) {
	bool outside = true;
	for (auto& pixel : *player.getPixels()) {
		if ((pixel.coord + player.getAnchor()).y > anchor.y && (pixel.coord + player.getAnchor()).y < anchor.y + laneWidth + 2) {
			outside = false;
			break;
		}
	}
	if (outside) return false;
	for (auto& obstacle : obstacles) {
		if (obstacle->checkCollision(&player)) return true;
	}
	return false;
}