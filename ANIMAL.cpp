#include "ANIMAL.h"

AnimalLane::AnimalLane(Tree& _t, int _laneNumber, int _level, int _laneWidth = 5) :
	t (&_t), laneNumber(_laneNumber), level(_level), laneWidth(_laneWidth), anchor(0, _laneNumber * _laneWidth) {
	drawLane();
	srand(time(NULL));
	resetSpawn();
	resetMove();
	goRight = rand() & 1;
}
void AnimalLane::drawLane() {
	gotoxy(anchor);
	cout << g_laneline;
	gotoxy(anchor.x, anchor.y + laneWidth);
	cout << g_laneline;
}
bool AnimalLane::run() {
	if (spawnCooldown <= 0) {
		spawnAnimal();
		resetSpawn();
	}
	else --spawnCooldown;
	if (moveCooldown <= 0) {
		for (Animal* animal : animals) {
			animal->move(goRight);
		}
		OXY pos = animals.begin()->getPos();
		if (pos.x < 0 || pos.x > ConsoleWidth) {
			delete *(animals.begin());
			animals.pop_front();
		}
		resetMove();
	}
	else --moveCooldown;
	return checkCollision();
}
void AnimalLane::resetSpawn() {
	spawnCooldown = (DEFAULT_SPAWN_SPEED - LEVEL_SPAWN_SPEED * level);
}
void AnimalLane::resetMove() {
	moveCooldown = (DEFAULT_MOVE_SPEED - LEVEL_MOVE_SPEED * level);
}
void AnimalLane::spawnAnimal() {
	int animal_type = rand() % ANIMAL_TYPE;
	Animal* animal = nullptr;
	OXY pos = (goRight ? {0, anchor.y} : {ConsoleWidth, anchor.y});
	switch (animal_type) {
	case 0: animal = new Pigeon(pos); break;
	case 1: animal = new Dog(pos); break;
	case 2: animal = new Pterodactyl(pos); break;
	default: animal = new Dino(pos); break;
	}
	animals.push_back(animal);
}
bool AnimalLane::checkCollision(player& A) {
	OXY player_pos = A.position();
	if (player_pos.y >= anchor.y && player_pos <= anchor.y + laneWidth) {
		for (Animal* animal : animals) {
			if (animal->checkCollision(player_pos)) return true;
		}
	}
	return false;	
}
void Animal::playsound(string file) {
	PlaySound(file, NULL, SND_ASYNC | SND_FILENAME);
}
bool Animal::checkCollision(OXY other) {
	for (OXY pixel : *pixels) {
		if (anchor + pixel == other) return true;
	}
	return false;
}
OXY Animal::getPos() {
	return anchor;
}
void Animal::draw() {
	for (OXY pixel : *pixels) {
		gotoxy(anchor + pixel);
		cout << char(178);
	}
}
void Animal::move(bool goRight) {
	anchor.x += (goRight ? 1 : -1);
}

void Pigeon::speak() {
	playsound(PIGEON_SOUND_FILE);
}
void Dog::speak() {
	playsound(DOG_SOUND_FILE);
}
void Pterodactyl::speak() {
	playsound(PTERODACTYL_SOUND_FILE);
}
void Dino::speak() {
	playsound(DINO_SOUND_FILE);
}