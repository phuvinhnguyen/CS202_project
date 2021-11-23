#include "Header.h"
using namespace std;


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
inGame::inGame() {}
inGame::~inGame() {}
int inGame::loadGame(int level, string filePath, bool music)
{
    int land_num;
    bool newlv = 0;
    ifstream ifs(filePath, ios::binary);
    if (!ifs.good()) {
        score = 0;
        level_ = level;
        land_num = rand() % 6 + 4;
        for (int i = 0; i < land_num; i++) {
            land_.push_back(rand() % 2);
        }
    }
    else {
        ifs.read((char*)&score, 4);
        ifs.read((char*)&level_, 1);
        level = level_;
        int32_t s;
        ifs.read((char*)&s, 4);
        for (int i = 0; i < s; i++) {
            bool a;
            ifs.read((char*)&a, 1);
            land_.push_back(a);
        }
        land_num = land_.size();
    }
    ifs.close();
newlevel:
    if (newlv) {
        score += level_;
        land_num = rand() % 6 + 4;
        land_.clear();
        for (int i = 0; i < land_num; i++) {
            land_.push_back(rand() % 2);
        }
        level_++;
    }
    newlv = 1;
restart:
    Tree tree;
    player plr;
    int land_width = (ConsoleHeight - 4) / land_num - 1;
    vector<land*> land__;
    for (int i = 0; i < land_num; i++) {
        if (land_[i])
            land__.push_back(new animalLane(tree, (land_width + 1) * i + 2, level, land_width));
        else
            land__.push_back(new carLane(tree, (land_width + 1) * i + 2, level, land_width));
    }


    system("cls");
    while (1) {
        Score(score);
        if (plr.position().y <= 2) {
            Win();
            if (music) PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
            score += level;
            for (int i = 0; i < land_num; i++) delete land__[i];
            goto newlevel;
        }
        char x = plr.run();
        if (x == 'q') {
            break;
        }
        else if (x == 'v') {
            music = !music;
        }
        else if (x == 'r') {
            saveFile();
        }
        if (tree.exist(plr.position())) {
            score--;
            Dead();
            if (music) PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
            plr.reset();
        }
        for (int i = 0; i < land_num; i++) {
            land__[i]->run();
        }
        if (tree.exist(plr.position())) {
            score--;
            Dead();
            if (music) PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
            plr.reset();
        }
    }
    return 1;
}
