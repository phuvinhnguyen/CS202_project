#include "Header.h"

extern int background[ConsoleWidth][ConsoleHeight];

JurassicRoad::JurassicRoad(int _level, int _difficulty, InGame* _ingame)
	: ingame(_ingame), level(_level), difficulty(_difficulty), player(OXY(PLAYER_DEF_POS_X, PLAYER_DEF_POS_Y)) {
	memset(background, 0, sizeof(background));
	switch (level) {
	case 1: {
		int cury = ScreenTop - 6;
		Lane* lane;
		lane = new SimpleLane<Pigeon>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Cougar>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	case 2: {
		int cury = ScreenTop - 6;
		Lane* lane;
		lane = new SimpleLane<Car>(OXY(ScreenLeft, cury += 7), 5, difficulty, 1, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Pterodactyl>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Ceratosaurus>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	case 3: {
		int cury = ScreenTop - 6;
		Lane* lane;
		lane = new SimpleLane<Ceratosaurus>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Cougar>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Car>(OXY(ScreenLeft, cury += 7), 5, difficulty, 1, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Pterodactyl>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	case 4: {
		int cury = ScreenTop - 6;
		Lane* lane;
		lane = new SimpleLane<Car>(OXY(ScreenLeft, cury += 7), 5, difficulty, 1, 0);
		lanes.push_back(lane);
		lane = new SimpleLane<Cougar>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, 0);
		lanes.push_back(lane);
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 60, 0);
		lanes.push_back(lane);
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 60, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	case 5: {
		int cury = ScreenTop - 6;
		Lane* lane;
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 80, 0);
		lanes.push_back(lane);
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 100, 0);
		lanes.push_back(lane);
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 80, 0);
		lanes.push_back(lane);
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 50, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	case 6: {
		int cury = ScreenTop - 8;
		Lane* lane;
		lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 39, difficulty, 1, 1);
		lanes.push_back(lane);
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 20));
		break;
	}
	case 7: {
		int cury = ScreenTop - 6;
		Lane* lane;
		for (int i = 0; i < 4; ++i) {
			int choice = rand() % 6;
			int k = (i == 3);
			switch (choice) {
			case 0: 
				lane = new SimpleLane<Pigeon>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, k);
				break;
			case 1:
				lane = new SimpleLane<Pterodactyl>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, k);
				break;
			case 2:
				lane = new SimpleLane<Car>(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 2, k);
				break;
			case 3:
				lane = new SimpleLane<Cougar>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, k);
				break;
			case 4:
				lane = new SimpleLane<Ceratosaurus>(OXY(ScreenLeft, cury += 7), 5, difficulty, 0, k);
				break;
			case 5:
				lane = new ChaoticLane(OXY(ScreenLeft, cury += 7), 5, difficulty, rand() % 100 < 60, k);
				break;
			}
			lanes.push_back(lane);
		}
		player.setDefPos(OXY(PLAYER_DEF_POS_X, cury + 10));
		break;
	}
	}
}

JurassicRoad::~JurassicRoad() {
	for (auto& lane : lanes) {
		delete lane;
	}
}

int JurassicRoad::run() {
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	int cooldown = 10000;
	if (level == 6) cooldown = 0;
	int DIFFICULTY = difficulty;
	int idontknowwhatthisdoes = 1000000;
	bool first = true;
	SetConsoleTextAttribute(console_color, 15);
	double score = 0;
	player.draw();
	auto BEG = chrono::steady_clock::now();
	while (true) {
		if (level == 6) score += DIFFICULTY / 10000.0;
		auto st = chrono::steady_clock::now();
		for (auto& lane : lanes) {
			lane->run(DIFFICULTY);
		}
		if (level == 6) {
			if (idontknowwhatthisdoes <= 0) {
				idontknowwhatthisdoes = 1000000;
				if (DIFFICULTY < 20) ++DIFFICULTY;
			}
			else --idontknowwhatthisdoes;
		}
		if (cooldown == 10000) {
			gotoxy(player.getAnchor().x-5, player.getAnchor().y - 1);
			SetConsoleTextAttribute(console_color, 15);
			cout << "                                ";
			gotoxy(player.getAnchor().x-1, player.getAnchor().y - 1);
			cout << WHITE << "READY";
			--cooldown;
		}
		else if (cooldown == 5000) {
			gotoxy(player.getAnchor().x-5, player.getAnchor().y - 1);
			SetConsoleTextAttribute(console_color, 15);
			cout << "                                ";
			gotoxy(player.getAnchor().x, player.getAnchor().y - 1);
			cout << WHITE << "GO";
			--cooldown;
		}
		else if (cooldown <= 0) {
			if (first) {
				gotoxy(player.getAnchor().x-5, player.getAnchor().y - 1);
				SetConsoleTextAttribute(console_color, 15);
				cout << "                                ";
				while (_kbhit()) {
					char ch = _getch();
				}
				first = false;
			}
			if (player.run()) {
				while (true) {
					int choice = ingame->pauseMenu(50, 12);
					if (choice == 0) {
						resume();
						break;
					}
					else if (choice == 2) {
						return 2;
					}
				}
			};
		}
		else --cooldown;
		while (true) {
			long long duration = chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - st).count();
			if (duration > 150000 || duration < 0) break;
		}
		if (checkDeath()) {
			if (level == 6) {
				auto ED = chrono::steady_clock::now();
				long long duration = chrono::duration_cast<chrono::seconds>(ED - BEG).count();
				if (ingame->hasSound) {
					PlaySound(L"game_over.wav", NULL, SND_FILENAME);
					PlaySound(L"background_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				}
				SetConsoleTextAttribute(console_color, 15);
				system("cls");
				gotoxy(30, 10);
				cout << "-----------------------------------------";
				gotoxy(30, 11);
				cout << "|   YOU DIED";
				gotoxy(70, 11);
				cout << "|";
				gotoxy(30, 12);
				cout << "|   SURVIVAL TIME: " << duration << "s";
				gotoxy(70, 12);
				cout << "|";
				gotoxy(30, 13);
				cout << "|   YOUR SCORE: " << round(score) << " points";
				gotoxy(70, 13);
				cout << "|";
				gotoxy(30, 14);
				cout << "-----------------------------------------";
				while (_kbhit()) {
					char a = _getch();
				}
				while (!_kbhit()) {

				}
				char a = _getch();
			}
			return 0;
		}
		else if (level != 6 && checkWin()) {
			return 1;
		}
		SetConsoleTextAttribute(console_color, 15);
	}
}

bool JurassicRoad::checkDeath() {
	for (auto& lane : lanes) {
		if (lane->checkCollision(player)) {
			return true;
		}
	}
	return false;
}

bool JurassicRoad::checkWin() {
	if (player.getAnchor().y == ScreenTop) return true;
	return false;
}

void JurassicRoad::resume() {
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 15);
	system("cls");
	memset(background, 0, sizeof(background));
	for (auto itr = lanes.begin(); itr != lanes.end(); ++itr) {
		auto tmp = itr;
		++tmp;
		(*itr)->resumeLane(tmp == lanes.end());
	}
	player.draw();
	gotoxy(40, 2);
	cout << "LEVEL: ";
	if (level == 6) cout << "SURVIVAL";
	else if (level == 7) cout << "ENDLESS";
	else cout << level;
	gotoxy(40, 3);
	cout << "DIFFICULTY: " << difficulty;
}