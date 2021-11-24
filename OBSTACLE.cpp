#include "Header.h"

vector < Pixel > g_PlayerPixel;

vector < Pixel > g_PigeonPixel_r;
vector < Pixel > g_PterodactylPixel_r;
vector < Pixel > g_PlanePixel_r;
vector < Pixel > g_CougarPixel_r;
vector < Pixel > g_CarPixel_r;
vector < Pixel > g_CeratosaurusPixel_r;

vector < Pixel > g_PigeonPixel_l;
vector < Pixel > g_PterodactylPixel_l;
vector < Pixel > g_PlanePixel_l;
vector < Pixel > g_CougarPixel_l;
vector < Pixel > g_CarPixel_l;
vector < Pixel > g_CeratosaurusPixel_l;

Pixel blankPixel(OXY(0, 0), ' ', WHITE);

extern int background[ConsoleWidth][ConsoleHeight];

void loadCharacters() {
	loadTexture("player.txt", &g_PlayerPixel, WHITE);

	loadTexture("pigeon_r.txt", &g_PigeonPixel_r, WHITE);
	loadTexture("cougar_r.txt", &g_CougarPixel_r, CYAN);
	loadTexture("car_r.txt", &g_CarPixel_r, YELLOW);
	loadTexture("ceratosaurus_r.txt", &g_CeratosaurusPixel_r, WHITE);
	loadTexture("pterodactyl_r.txt", &g_PterodactylPixel_r, GREEN);
	loadTexture("plane_r.txt", &g_PlanePixel_r, RED);

	loadTexture("pigeon_l.txt", &g_PigeonPixel_l, WHITE);
	loadTexture("cougar_l.txt", &g_CougarPixel_l, CYAN);
	loadTexture("car_l.txt", &g_CarPixel_l, YELLOW);
	loadTexture("ceratosaurus_l.txt", &g_CeratosaurusPixel_l, WHITE);
	loadTexture("pterodactyl_l.txt", &g_PterodactylPixel_l, GREEN);
	loadTexture("plane_l.txt", &g_PlanePixel_l, RED);
}

void loadTexture(const char* path, vector < Pixel >* g_pixels, const char* color) {
	memset(background, 0, sizeof(background));
	ifstream ifs(path);
	if (!ifs.good()) return;
	int y = 0;
	while (!ifs.eof()) {
		string s;
		getline(ifs, s);
		for (int x = 0; x < s.size(); ++x) {
			if (s[x] != ' ') {
				g_pixels->push_back(Pixel(OXY(x, y), s[x], color));
			}
		}
		++y;
	}
	ifs.close();
}

Character::Character(OXY _anchor, vector < Pixel >* _pixels, int _defCooldown)
	: anchor(_anchor), pixels(_pixels), defCooldown(_defCooldown), cooldown(0) { }
Character::~Character() { }

void Character::resetCooldown() {
	cooldown = defCooldown;
}
OXY Character::getAnchor() {
	return anchor;
}
bool Character::checkCollision(Character* other) {
	if (abs(other->anchor.x - anchor.x) > 30 || abs(other->anchor.y - anchor.y) > 5) return false;
	set < pair < int, int > > S;
	for (auto& pixel : *pixels) {
		pair < int, int > realCoord(anchor.x + pixel.coord.x, anchor.y + pixel.coord.y);
		S.insert(realCoord);
	}
	for (auto& pixel : *other->pixels) {
		pair < int, int > realCoord(other->anchor.x + pixel.coord.x, other->anchor.y + pixel.coord.y);
		if (S.count(realCoord)) return true;
	}
	return false;
}

Player::Player(OXY _anchor)
	: Character(_anchor, &g_PlayerPixel, PLAYER_SPEED), prevAnchor(OXY(0, 0)) { }
Player::~Player() { }
vector < Pixel >* Player::getPixels() {
	return pixels;
}
void Player::setDefPos(OXY _anchor) {
	anchor = _anchor;
}

bool Player::run() {
	if (cooldown <= 0) {
		if (_kbhit()) {
			char ch;
			do {
				ch = _getch();
			} while (_kbhit());
			prevAnchor = anchor;
			switch (ch) {
			case 'a': {--anchor.x; break; }
			case 'd': {++anchor.x; break; }
			case 'w': {--anchor.y; break; }
			case 's': {++anchor.y; break; }
			case 'p': {return true; }
			}
			bool good = true;
			for (auto& pixel : *pixels) {
				if ((pixel.coord + anchor).invalid()) {
					good = false;
					break;
				}
			}
			if (good) {
				erase(false);
				draw();
				resetCooldown();
			}
			else {
				anchor = prevAnchor;
			}
		}
	}
	else --cooldown;
	return false;
}
void Player::draw() {
	for (auto pixel : *pixels) {
		cout << pixel + anchor;
	}
}
void Player::erase(bool curPos) {
	OXY realAnchor = (curPos ? anchor : prevAnchor);
	for (auto pixel : *pixels) {
		OXY realCoord = pixel.coord + realAnchor;
		cout << blankPixel + realCoord;
	}
}

Obstacle::Obstacle(OXY _anchor, vector < Pixel >* _pixels, int _power, int _defCooldown, bool _goRight)
	: Character(_anchor, _pixels, _defCooldown), goRight(_goRight), power(_power), isMoving(true) { }
Obstacle::~Obstacle() { }

bool Obstacle::isOffScreen() {
	if (goRight) {
		if (anchor.x >= ConsoleWidth) return true;
		return false;
	}
	else {
		if (anchor.x >= ScreenLeft) return false;
		for (auto& pixel : *pixels) {
			if (!(pixel.coord + anchor).invalid()) return false;
		}
		return true;
	}
}
int Obstacle::getPower() {
	return power;
}
void Obstacle::draw() {
	for (auto& pixel : *pixels) {
		cout << pixel + anchor;
	}
}
void Obstacle::setMove(bool move) {
	return;
}

void Obstacle::erase(bool curPos) {
	OXY realAnchor = anchor;
	if (!curPos) realAnchor = realAnchor + OXY(goRight ? -1 : 1, 0);
	for (auto& pixel : *pixels) {
		OXY realCoord = pixel.coord + realAnchor;
		cout << blankPixel + realCoord;
	}
}
bool Obstacle::move() {
	if (!isMoving) return false;
	if (cooldown <= 0) {
		anchor.x += (goRight ? 1 : -1);
		resetCooldown();
		return true;
	}
	cooldown -= 1;
	return false;
}

#define offset_x -20
Pigeon::Pigeon(OXY _anchor, int level, bool _goRight, int laneWidth) 
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 0) + 1), (_goRight ? &g_PigeonPixel_r : &g_PigeonPixel_l) , PIGEON_POWER, PIGEON_DEF_SPEED - level * PIGEON_LVL_SPEED, _goRight) { }
Pigeon::~Pigeon() { }
void Pigeon::speak() {
	playSound(PIGEON_SOUND_FILE);
}

Pterodactyl::Pterodactyl(OXY _anchor, int level, bool _goRight, int laneWidth)
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 2) + 1), (_goRight ? &g_PterodactylPixel_r : &g_PterodactylPixel_l), PTERODACTYL_POWER, PTERODACTYL_DEF_SPEED - level * PTERODACTYL_LVL_SPEED, _goRight) { }
Pterodactyl::~Pterodactyl() { }
void Pterodactyl::speak() {
	playSound(PTERODACTYL_SOUND_FILE);
}

Plane::Plane(OXY _anchor, int level, bool _goRight, int laneWidth)
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 4) + 1), (_goRight ? &g_PlanePixel_r : &g_PlanePixel_l), PLANE_POWER, PLANE_DEF_SPEED - level * PLANE_LVL_SPEED, _goRight) { }
Plane::~Plane() { }
void Plane::speak() {
	playSound(PLANE_SOUND_FILE);
}

Cougar::Cougar(OXY _anchor, int level, bool _goRight, int laneWidth) 
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 3) + 1), (_goRight ? &g_CougarPixel_r : &g_CougarPixel_l), COUGAR_POWER, COUGAR_DEF_SPEED - level * COUGAR_LVL_SPEED, _goRight) { }
Cougar::~Cougar() { }
void Cougar::speak() {
	playSound(COUGAR_SOUND_FILE);
}
Ceratosaurus::Ceratosaurus(OXY _anchor, int level, bool _goRight, int laneWidth) 
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 4) + 1), (_goRight ? &g_CeratosaurusPixel_r : &g_CeratosaurusPixel_l), CERATOSAURUS_POWER, CERATOSAURUS_DEF_SPEED - level * CERATOSAURUS_LVL_SPEED, _goRight) { }
Ceratosaurus::~Ceratosaurus() { } 
void Ceratosaurus::speak() {
	playSound(CERATOSAURUS_SOUND_FILE);
}

Car::Car(OXY _anchor, int level, bool _goRight, int laneWidth)
	: Obstacle(_anchor + OXY((_goRight ? offset_x : ConsoleWidth), rand() % (laneWidth - 1) + 1), (_goRight ? &g_CarPixel_r : &g_CarPixel_l), CAR_POWER, CAR_DEF_SPEED - level * CAR_LVL_SPEED, _goRight) { }
Car::~Car() { }
void Car::speak() {
	playSound(CAR_SOUND_FILE);
}
void Car::setMove(bool move) {
	isMoving = move;
}