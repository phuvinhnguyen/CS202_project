#include "INGAME.h"
using namespace std;


int laneWidthCalculate(vector<laneData> a) {
    return (ConsoleHeight - 10) / a.size();
}
void inGame::Dead(int x, int y) {
    gotoxy(x, y);
    cout << "--------------------------";
    gotoxy(x, y + 1);
    cout << "|        YOU DEAD        |";
    gotoxy(x, y + 2);
    cout << "|press any key to restart|";
    gotoxy(x, y + 3);
    cout << "--------------------------";
    while (1)
    {
        if (_kbhit()) break;
    }
    gotoxy(x, y);
    cout << "                          ";
    gotoxy(x, y + 1);
    cout << "                          ";
    gotoxy(x, y + 2);
    cout << "                          ";
    gotoxy(x, y + 3);
    cout << "                          ";
}
void inGame::Win(int x, int y) {
    gotoxy(x, y);
    cout << "---------------------------";
    gotoxy(x, y + 1);
    cout << "|         YOU WIN         |";
    gotoxy(x, y + 2);
    cout << "|press any key to continue|";
    gotoxy(x, y + 3);
    cout << "---------------------------";
    while (1)
    {
        if (_kbhit()) break;
    }
    gotoxy(x, y);
    cout << "                           ";
    gotoxy(x, y + 1);
    cout << "                           ";
    gotoxy(x, y + 2);
    cout << "                           ";
    gotoxy(x, y + 3);
    cout << "                           ";
}
void inGame::Score(int x, int y) {
    gotoxy(x, y);
    cout << "-----------------------";
    gotoxy(x, y + 1);
    cout << "|your score: " << SCORE;
    gotoxy(x, y + 2);
    cout << "-----------------------";
}
inGame::inGame():LEVEL(0), SCORE(0) {}
inGame::~inGame() {}
void inGame::loadGame(int level, string filePath, bool music)
{
    SOUND = music;

    //load game data
    LEVEL = level;
    loadFile(filePath);

    vector<land> LANE;
    for (int i = 0;; i++)
    {
        //pre-prepare
        if (i > 0) newData();
        Tree tree;
        player plr(50, 46);
        int lane_width = laneWidthCalculate(LANE_DATA);

        //pre-prepare
        for (int j = 0; j < LANE_DATA.size(); j++) {
            switch (LANE_DATA[j].carLane) {
            case true:
                LANE.push_back(land(&tree, j * (lane_width + 1) + 5, LEVEL, lane_width, LANE_DATA[j].goRight, 1, LANE_DATA[j].x_init, LANE_DATA[j].red, LANE_DATA[j].green));
                break;
            case false:
                LANE.push_back(land(&tree, j * (lane_width + 1) + 5, LEVEL, lane_width, LANE_DATA[j].goRight, 0));
                break;
            }
        }

        //run game
        for (int i = 0; i < LANE_DATA.size(); i++)
            LANE[i].init();
        system("cls");
        while (1) {
            Score();
            if (plr.position().y <= 3) {
                if (music) PlaySound(WIN_SOUND_FILE, NULL, SND_FILENAME | SND_ASYNC);
                Win();
                SCORE += level;
                LANE.clear();
                break;
            }

            if (options(plr.run())) return;

            if (tree.exist(plr.position())) {
                SCORE--;
                if (music) PlaySound(LOSE_SOUND_FILE, NULL, SND_FILENAME | SND_ASYNC);
                Dead();
                plr.reset();
            }

            for (int i = 0; i < LANE_DATA.size(); i++) {
                LANE[i].run(music);
                gotoxy(0, i * (lane_width + 1) + 4);
                cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -";
            }

            if (tree.exist(plr.position())) {
                SCORE--;
                if (music) PlaySound(LOSE_SOUND_FILE, NULL, SND_FILENAME | SND_ASYNC);
                Dead();
                plr.reset();
            }
        }
    }
}
void inGame::saveFile(int x, int y) {
    while (1) {
        gotoxy(x, y);
        cout << "-----------------------------------------------------------------------------";
        gotoxy(x, y + 1);
        cout << "enter file location:                                                         ";
        gotoxy(x, y + 2);
        cout << "enter file name:                                                             ";
        gotoxy(x, y + 3);
        cout << "-----------------------------------------------------------------------------";

        gotoxy(x + 24, y + 1);
        string dir;
        cin >> dir;
        gotoxy(x + 20, y + 2);
        string file;
        cin >> file;

        ofstream ofs(dir + "\\" + file, ios::binary);
        if (!ofs.good()) {
            gotoxy(x + 15, y + 3);
            cout << "|     FILE CANNOT OPEN      |";
        }
        else {
            ofs.write((char*)&SCORE, 4);
            ofs.write((char*)&LEVEL, 4);
            int32_t s = LANE_DATA.size();
            ofs.write((char*)&s, 4);
            for (int i = 0; i < LANE_DATA.size(); i++)
            {
                laneData a = LANE_DATA[i];
                ofs.write((char*)&a, sizeof(laneData));
            }
            gotoxy(x + 15, y + 3);
            cout << "|     SUCCESS      |";
        }
        ofs.close();
        gotoxy(x + 1, y + 4);
        cout << "re-save file? y/n:                                ";
        char a = _getch();
        if (a == 'n') break;
    }

    gotoxy(1, 1);
    cout << "                                                                             ";
    gotoxy(1, 2);
    cout << "                                                                             ";
    gotoxy(1, 3);
    cout << "                                                                             ";
    gotoxy(1, 4);
    cout << "                                                                             ";
    gotoxy(1, 5);
    cout << "                                                        ";
}
bool inGame::loadFile(string dir) {
    ifstream ifs(dir, ios::binary);
    if (!ifs.good()) {
        ifs.close();
        SCORE = 0;
        int LANE_DATAnumber = rand() % MAX_LANE_NUM + MIN_LANE_NUM;
        for (int i = 0; i < LANE_DATAnumber; i++) {
            LANE_DATA.push_back(laneData(rand() % 2, rand() % 2, RED_LIGHT_TIME + rand() % RAND_LIGHT_TIME, GREEN_LIGHT_TIME + rand() % RAND_LIGHT_TIME, _X_INIT_LEFT + rand() % _X_INIT_RANGE));
        }
        return 0;
    }
    else {
        ifs.read((char*)&SCORE, 4);
        ifs.read((char*)&LEVEL, 4);
        int32_t s;
        ifs.read((char*)&s, 4);
        LANE_DATA.clear();
        for (int i = 0; i < s; i++) {
            laneData a;
            ifs.read((char*)&a, sizeof(laneData));
            LANE_DATA.push_back(a);
        }
        ifs.close();
        return 1;
    }
}
void inGame::newData() {
    int lanenumber = rand() % MAX_LANE_NUM + MIN_LANE_NUM;
    LANE_DATA.clear();
    LEVEL++;
    for (int i = 0; i < lanenumber; i++) {
        LANE_DATA.push_back(laneData(rand() % 2, rand() % 2, RED_LIGHT_TIME + rand() % RAND_LIGHT_TIME, GREEN_LIGHT_TIME + rand() % RAND_LIGHT_TIME, _X_INIT_LEFT + rand() % _X_INIT_RANGE));
    }
}
bool inGame::options(char a) {
    if (a == 'q') return true;
    else if (a == 'r') saveFile();
    else if (a == 'v') SOUND = !SOUND;
    return false;
}