#include "Header.h"

TrafficLight::TrafficLight(OXY _anchor)
	: anchor(_anchor.x - 5, _anchor.y), state(0), defCooldown(LIGHT_DEF_SPEED), cooldown(rand() % LIGHT_DEF_SPEED) { }
TrafficLight::~TrafficLight() { }

void TrafficLight::resetCooldown() {
	cooldown = defCooldown;
}

bool TrafficLight::isRed() {
	return state == 2;
}

void TrafficLight::switchLight() {
	(state += 1) %= 3;
}

void TrafficLight::run() {
	if (cooldown <= 0) {
		switchLight();
		draw();
		resetCooldown();
	}
	else --cooldown;
}

void TrafficLight::draw() {
	gotoxy(anchor);
	if		(state == 0)	cout << GREEN;
	else if (state == 1)	cout << YELLOW;
	else					cout << RED;
	cout << char(178);
}