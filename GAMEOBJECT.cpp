#include "LANE.h"
using namespace std;

vector < OXY > g_pigeonpixel = { OXY(0,0) };
vector < OXY > g_pterodactylpixel = { OXY(0,0) };
vector < OXY > g_dogpixel = { OXY(0,0) };
vector < OXY > g_dinopixel = { OXY(0,0) };
vector < OXY > g_carpixel = { OXY(0,0) };
vector < OXY > g_truckpixel = { OXY(0,0) };
vector < OXY > g_alienpixel = { OXY(0,0) };
vector < OXY > g_bikepixel = { OXY(0,0) };

vector < OXY > g_pigeonhead = { OXY(0,0) };
vector < OXY > g_pterodactylhead = { OXY(0,0) };
vector < OXY > g_doghead = { OXY(0,0) };
vector < OXY > g_dinohead = { OXY(0,0) };
vector < OXY > g_carhead = { OXY(0,0) };
vector < OXY > g_truckhead = { OXY(0,0) };
vector < OXY > g_alienhead = { OXY(0,0) };
vector < OXY > g_bikehead = { OXY(0,0) };

vector < OXY > g_pigeontail = { OXY(0,0) };
vector < OXY > g_pterodactyltail = { OXY(0,0) };
vector < OXY > g_dogtail = { OXY(0,0) };
vector < OXY > g_dinotail = { OXY(0,0) };
vector < OXY > g_cartail = { OXY(0,0) };
vector < OXY > g_trucktail = { OXY(0,0) };
vector < OXY > g_alientail = { OXY(0,0) };
vector < OXY > g_biketail = { OXY(0,0) };



gameObj::gameObj(Tree* _t, OXY init, bool _goRight, int _level) : pos(init), goRight(_goRight), count(0), alive(1){
	COUNTLOOP = DEFAULT_MOVE_SPEED + _level * LEVEL_MOVE_SPEED + rand() % RANDOM_MOVE_SPEED;
	tr = _t;
}
gameObj::~gameObj(){}
void gameObj::move() {
	if (count < COUNTLOOP) {
		count++;
		return;
	}
	count = 0;

	if (pos.x < -10 || pos.x > ConsoleWidth + 10) {
		alive = 0;
		return;
	}

	for (int i = 0; i < pixels_head.size(); i++) {
		if (tr->exist(pos + pixels_head[i] + mov_vec)) {
			if (!moral)
			{
				alive = 0;
				rm();
			}
			return;
		}
	}

	for (int i = 0; i < pixels_head.size(); i++) {
		tr->insert(pos + pixels_head[i] + mov_vec);
		tr->remove(pos + pixels_head[i]);
	}

	for (int i = 0; i < pixels_body.size(); i++) {
		tr->insert(pos + pixels_body[i] + mov_vec);
		tr->remove(pos + pixels_body[i]);
	}

	for (int i = 0; i < pixels_tail.size(); i++) {
		tr->insert(pos + pixels_tail[i] + mov_vec);
		tr->remove(pos + pixels_tail[i]);
		gotoxy(pos + pixels_tail[i]);
		cout << " ";
	}

	pos = pos + mov_vec;

	draw(pos);
}
void gameObj::rm() {
	for (int i = 0; i < pixels_head.size(); i++) {
		tr->remove(pos + pixels_head[i]);
		gotoxy(pos + pixels_head[i]);
		cout << " ";
	}
	for (int i = 0; i < pixels_tail.size(); i++) {
		tr->remove(pos + pixels_tail[i]);
		gotoxy(pos + pixels_tail[i]);
		cout << " ";
	}
	for (int i = 0; i < pixels_body.size(); i++) {
		tr->remove(pos + pixels_body[i]);
		gotoxy(pos + pixels_body[i]);
		cout << " ";
	}
	pixels_head.clear();
	pixels_body.clear();
	pixels_tail.clear();
}

dog::dog(Tree* _t, int level, OXY init, bool _goRight) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_doghead;
	pixels_body = g_dogpixel;
	pixels_tail = g_dogtail;
	moral = 0;
	draw(pos);
}
void dog::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "D";
}
void dog::speak() {
	
}
dog::~dog() {
	rm();
}

dino::dino(Tree* _t, int level, OXY init, bool _goRight) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_dinohead;
	pixels_body = g_dinopixel;
	pixels_tail = g_dinotail;
	moral = 0;
	draw(pos);
}
void dino::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "d";
}
void dino::speak() {

}
dino::~dino() {
	rm();
}

pterodactyl::pterodactyl(Tree* _t, int level, OXY init, bool _goRight) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_pterodactylhead;
	pixels_body = g_pterodactylpixel;
	pixels_tail = g_pterodactyltail;
	moral = 0;
	draw(pos);
}
void pterodactyl::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "P";
}
void pterodactyl::speak() {

}
pterodactyl::~pterodactyl() {
	rm();
}

pigeon::pigeon(Tree* _t, int level, OXY init, bool _goRight ) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_pigeonhead;
	pixels_body = g_pigeonpixel;
	pixels_tail = g_pigeontail;
	moral = 0;
	draw(pos);
}
void pigeon::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "P";
}
void pigeon::speak() {

}
pigeon::~pigeon() {
	rm();
}


car::car(Tree* _t, int level, OXY init, bool _goRight ) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_carhead;
	pixels_body = g_carpixel;
	pixels_tail = g_cartail;
	moral = rand() % 2;
	draw(pos);
}
void car::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "C";
}
void car::speak() {

}
car::~car() {
	rm();
}

truck::truck(Tree* _t, int level, OXY init, bool _goRight ) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_truckhead;
	pixels_body = g_truckpixel;
	pixels_tail = g_trucktail;
	moral = rand() % 2;
	draw(pos);
}
void truck::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "T";
}
void truck::speak() {

}
truck::~truck() {
	rm();
}

alien::alien(Tree* _t, int level, OXY init, bool _goRight ) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_alienhead;
	pixels_body = g_alienpixel;
	pixels_tail = g_alientail;
	moral = rand() % 2;
	draw(pos);
}
void alien::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "A";
}
void alien::speak() {

}
alien::~alien() {
	rm();
}

bike::bike(Tree* _t, int level, OXY init, bool _goRight ) : gameObj(_t, init, _goRight, level) {
	if (goRight) mov_vec = OXY(1, 0);
	else mov_vec = OXY(-1, 0);
	pixels_head = g_bikehead;
	pixels_body = g_bikepixel;
	pixels_tail = g_biketail;
	moral = rand() % 2;
	draw(pos);
}
void bike::draw(OXY a) {
	gotoxy(a);
	if (pointAvailable(a)) cout << "A";
}
void bike::speak() {

}
bike::~bike() {
	rm();
}

/*
<^=[=]~
  UU UU

<O=(D)//
	W

 /DD\
CO---O

___/DDD|
L      |
LOO--OO-

*/

