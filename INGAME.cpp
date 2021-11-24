#ifndef INGAME
#define INGAME


#include "Header.h"
using namespace std;


int laneWidthCalculate(vector<char> a) {
    return (ConsoleHeight - 5) / a.size();
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
}
void inGame::Score(int num, int x, int y) {
    gotoxy(x, y);
    cout << "-----------------------";
    gotoxy(x, y + 1);
    cout << "|your score: " << num;
    gotoxy(x, y + 2);
    cout << "-----------------------";
}
inGame::inGame():level_(0), score(0) {}
inGame::~inGame() {}
void inGame::loadGame(int level, string filePath, bool music)
{
    //load game data
    level_ = level;
    loadFile(filePath);

    vector<land*> land__;
    for (int i = 0;; i++)
    {
        //pre-prepare
        if (i > 0) newData();
        Tree tree;
        player plr;
        int lane_width = laneWidthCalculate(land_);

        //pre-prepare
        for (int j = 0; j < land_.size(); j++) {
            switch (land_[j]) {
            case 32:
                land__.push_back(new animalLane(tree, j * (lane_width + 2) + 4, level_, lane_width, 1));
                break;
            case 33:
                land__.push_back(new animalLane(tree, j * (lane_width + 2) + 4, level_, lane_width, 0));
                break;
            case 34:
                land__.push_back(new carLane(tree, j * (lane_width + 2) + 4, level_, lane_width, 0));
                break;
            default:
                land__.push_back(new carLane(tree, j * (lane_width + 2) + 4, level_, lane_width, 1));
            }
        }

        //run game
        system("cls");
        while (1) {
            Score(score);
            if (plr.position().y <= 4) {
                if (music) PlaySound(win_sound, NULL, SND_FILENAME | SND_ASYNC);
                Win();
                score += level;
                for (int i = 0; i < land_.size(); i++) delete land__[i];
                land__.clear();
                break;
            }

            char x = plr.run();
            if (x == 'q') {
                for (int i = 0; i < land_.size(); i++) delete land__[i];
                land__.clear();
                return;
            }
            else if (x == 'v') {
                music = !music;
            }
            else if (x == 'r') {
                saveFile();
            }

            if (tree.exist(plr.position())) {
                score--;
                if (music) PlaySound(lose_sound, NULL, SND_FILENAME | SND_ASYNC);
                Dead();
                plr.reset();
            }

            for (int i = 0; i < land_.size(); i++) {
                land__[i]->run(music);
            }

            if (tree.exist(plr.position())) {
                score--;
                if (music) PlaySound(lose_sound, NULL, SND_FILENAME | SND_ASYNC);
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
            ofs.write((char*)&score, 4);
            ofs.write((char*)&level_, 4);
            int32_t s = land_.size();
            ofs.write((char*)&s, 4);
            for (int i = 0; i < land_.size(); i++)
            {
                char a = land_[i];
                ofs.write((char*)&a, 1);
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
        score = 0;
        int land_number = rand() % 2;
        for (int i = 0; i < land_number; i++) {
            land_.push_back(rand() % 4 + 32);
        }
        return 0;
    }
    else {
        ifs.read((char*)&score, 4);
        ifs.read((char*)&level_, 4);
        int32_t s;
        ifs.read((char*)&s, 4);
        land_.clear();
        for (int i = 0; i < s; i++) {
            char a;
            ifs.read((char*)&a, 1);
            land_.push_back(a);
        }
        ifs.close();
        return 1;
    }
}
void inGame::newData() {
    int land_number = rand() % 2;
    for (int i = 0; i < land_number; i++) {
        land_.push_back(rand() % 4 + 32);
    }
}
#endif // !INGAME
