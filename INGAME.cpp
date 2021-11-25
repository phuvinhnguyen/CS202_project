#include "Header.h"

bool InGame::Dead(int x, int y) {
    vector<string> options;
    options.push_back("Try again");
    options.push_back("Quit to menu");
    int choice = menu(x, y, options, "Game Over");
    return !choice;
}
bool InGame::Win(int x, int y) {
    vector<string> options;
    options.push_back("Continue");
    options.push_back("Quit to menu");
    int choice = menu(x, y, options, "Level Complete");
    return !choice;
}
void InGame::Score(int num, int x, int y)
{
    gotoxy(x, y);
    cout << "-----------------------";
    gotoxy(x, y + 1);
    cout << "|your score: " << num;
    gotoxy(x, y + 2);
    cout << "-----------------------";
}
InGame::InGame() : hasSound(1), maxlevel(1), level(1), score(0), game(nullptr), difficulty(3), endless_lvl(0) {
    PlaySound(L"background_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

InGame::~InGame() {}

bool InGame::loadGame(string filePath, bool music)
{
    ifstream ifs(filePath, ios::binary);
    if (!ifs.good())
    {
        CantLoadFile(30,20);
        ifs.close();
        return false;
    }
    else
    {
        ifs.read((char *)&score, 4);
        ifs.read((char *)&level, 4);
        ifs.read((char *)&difficulty, 4);
        ifs.read((char *)&maxlevel, 4);
        ifs.read((char*)&endless_lvl, 4);
        ifs.close();
        return true;
    }
    ifs.close();
}

void InGame::gameplay(int x, int y) {
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    while (level <= 7)
    {
        SetConsoleTextAttribute(console_color, 15);
        system("cls");
        maxlevel = max(maxlevel, level);
        game = new JurassicRoad(level, difficulty, this);
        gotoxy(40, 2);
        cout << "LEVEL: ";
        if (level == 6) cout << "SURVIVAL";
        else if (level == 7) cout << "ENDLESS";
        else cout << level;
        gotoxy(40, 3);
        cout << "DIFFICULTY: " << difficulty;
        int wtf = game->run();
        if (wtf == 1) { 
            if (level == 5) {
                if (hasSound) {
                    PlaySound(L"win.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
                    Sleep(10000);
                }
                SetConsoleTextAttribute(console_color, 15);
                system("cls");
                gotoxy(30, 10);
                cout << "---------------------------------------------------";
                gotoxy(30, 11);
                cout << "|   YOU WON!!!";
                gotoxy(80, 11);
                cout << "|";
                gotoxy(30, 12);
                cout << "|   You have successfully come home in one piece.";
                gotoxy(80, 12);
                cout << "|";
                gotoxy(30, 13);
                cout << "|   Mom is waiting for you inside. Come on in.";
                gotoxy(80, 13);
                cout << "|";
                gotoxy(30, 14);
                cout << "---------------------------------------------------";
                while (_kbhit()) char a = _getch();
                while (!_kbhit());
                char a = _getch();
            }
            else if (hasSound && level != 7) PlaySound(L"level_complete.wav", NULL, SND_FILENAME);
            if (hasSound && level != 7) PlaySound(L"background_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            if (level == 5) {
                maxlevel = 7;
                break;
            }
            else if (level != 7) ++level;
            else ++endless_lvl;
            maxlevel = max(maxlevel, level);
            if (level != 7) if (!Win(x, y)) return;
        }
        else if (wtf == 0)
        {
            fflush(stdin);
            if (level != 6) {
                if (hasSound) {
                    PlaySound(L"game_over.wav", NULL, SND_FILENAME);
                    PlaySound(L"background_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
                }
                if (level == 7) {
                    SetConsoleTextAttribute(console_color, 15);
                    system("cls");
                    gotoxy(30, 10);
                    cout << "-----------------------------------------";
                    gotoxy(30, 11);
                    cout << "|   YOU DIED";
                    gotoxy(70, 11);
                    cout << "|";
                    gotoxy(30, 12);
                    cout << "|   LEVEL COUNT: " << endless_lvl << " levels";
                    gotoxy(70, 12);
                    cout << "|";
                    gotoxy(30, 13);
                    cout << "|   YOUR SCORE: " << endless_lvl * difficulty << " points";
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
                    endless_lvl = 0;
                }
            }
            if (!Dead(x, y)) return;
        }
        else
        {
            delete game;
            return;
        }
        delete game;
    }
}
void InGame::CantLoadFile(int x, int y)
{
    gotoxy(x, y);
    cout << "---------------------------";
    gotoxy(x, y + 1);
    cout << "file cannot be loaded !";
    gotoxy(x, y + 2);
    cout << "---------------------------";
    while (!_kbhit())
    {
    }
    char a = _getch();
}

void InGame::saveFile(int x, int y)
{
    while (1)
    {
        gotoxy(x, y);
        cout << "----------------------------------------------------------------";
        gotoxy(x, y + 1);
        cout << "                        input directory                         ";
        gotoxy(x, y + 2);
        cout << "----------------------------------------------------------------";
        gotoxy(x, y + 3);
        cout << "|dir: ";
        gotoxy(x, y + 4);
        cout << "----------------------------------------------------------------";
        gotoxy(x + 7, y + 3);
        string dir;
        cin >> dir;

        ofstream ofs(dir, ios::binary);
        if (!ofs.good())
        {
            gotoxy(x, y + 4);
            cout << "|     file cannot open      |";
        }
        else
        {
            ofs.write((char *)&score, 4);
            ofs.write((char *)&level, 4);
            ofs.write((char *)&difficulty, 4);
            ofs.write((char *)&maxlevel, 4);
            ofs.write((char*)&endless_lvl, 4);
        }
        ofs.close();
        gotoxy(x, y+5);
        cout << "re-save file? y/n: ";
        char a;
        cin >> a;
        if (a == 'n')
            break;
    }

    gotoxy(x, y);
    cout << "                                                                             ";
    gotoxy(x, y + 1);
    cout << "                                                                             ";
    gotoxy(x, y + 2);
    cout << "                                                                             ";
    gotoxy(x, y + 3);
    cout << "                            ";
}

void InGame::readTitle(string dir, int x, int y)
{
    ifstream ifs(dir);
    string a;
    getline(ifs, a);
    while (a != "")
    {
        gotoxy(x, y);
        cout << a;
        a = "";
        getline(ifs, a);
        y++;
    }
    ifs.close();
}
string readDirectory(int x, int y)  {
    gotoxy(x, y);
    cout << "----------------------------------------------------------------";
    gotoxy(x, y + 1);
    cout << "                        input directory                         ";
    gotoxy(x, y + 2);
    cout << "----------------------------------------------------------------";
    gotoxy(x, y + 3);
    cout << "|dir: ";
    gotoxy(x, y + 4);
    cout << "----------------------------------------------------------------";
    gotoxy(x + 7, y + 3);
    string n;
    cin >> n;
    return n;
}
void InGame::gameTitle(int x, int y)
{
    readTitle("gd.txt", x, y);
}

bool InGame::gameMenu(int x, int y)
{
    vector<string> options;
    for (int i = 1; i <= 5; ++i)
    {
        string name = "Level ";
        options.push_back(name + to_string(i) + (i <= maxlevel ? " : UNLOCKED" : " : LOCKED"));
    }
    options.push_back(string("Level Survival") + (maxlevel >= 6 ? " : UNLOCKED" : " : LOCKED"));
    options.push_back(string("Level Endless") + (maxlevel >= 7 ? " : UNLOCKED" : " : LOCKED"));
    options.push_back("Return");

    int choice = menu(x, y, options, "CHOOSE LEVEL");
    if (choice == 7)
        return false;
    if (choice + 1 > maxlevel)
        return true;
    level = choice + 1;
    gameplay(x, y);
    return false;
}

bool InGame::difficultyMenu(int x, int y) {
    vector<string> options;
    options.push_back("Difficulty 1");
    options.push_back("Difficulty 2");
    options.push_back("Difficulty 3");
    options.push_back("Difficulty 4");
    options.push_back("Difficulty 5");
    options.push_back("Return");
    int choice = menu(x, y, options, "DIFFICULTY SELECTION");
    if (choice != 6) {
        difficulty = choice + 1;
    }
    return false;
}

bool InGame::saveMenu(int x, int y)
{
    system("cls");
    saveFile(20, 12);
    return false;
}

int InGame::pauseMenu(int x, int y)
{
    vector<string> options;
    options.push_back("Resume");
    options.push_back("Save game");
    options.push_back("Load game");
    options.push_back("Exit");
    int choice = menu(x, y, options, "PAUSE");
    while (true)
    {
        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            if (saveMenu(x, y))
                continue;
            return 1;
        case 2:
            if (loadMenu(x, y))
                continue;
            return 1;
        case 3:
            return 2;
        }
    }
}

bool InGame::startMenu(int x, int y)
{
    vector<string> options;
    options.push_back("New Game");
    options.push_back("Load Game");
    options.push_back("Exit");
    int choice = menu(x, y, options, "START");
    bool first = true;
    while (true)
    {
        switch (choice)
        {
        case 0:
            if (first) {
                hasSound = 1;
                maxlevel = 1;
                level = 1;
                score = 0;
                game = nullptr;
                difficulty = 3;
                endless_lvl = 0;
                first = false;
            }
            if (playMenu(x, y))
                continue;
            return true;
        case 1:
            if (loadMenu(x, y)) {
                choice = 0;
                first = false;
                continue;
            }
            return true;
        case 2:
            return false;
        }
    }
}

bool InGame::instructionMenu(int x, int y) {
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 15);
    system("cls");
    gameTitle(15, 3);
    gotoxy(x - 35, y - 1);
    cout << "------------------------------------------------------------------------------------------------";
    for (int i = 0; i <= 13; ++i) {
        gotoxy(x - 35, y + i); cout << "|";
        gotoxy(x + 60, y + i); cout << "|";
    }
    gotoxy(x - 35, y + 13);
    cout << "------------------------------------------------------------------------------------------------";
    gotoxy(x, y - 1);
    cout << "Instruction";
    gotoxy(x - 30, y);
    cout << "Welcome to JurrasicRoad, a simple road-crossing game";
    gotoxy(x - 30, y + 1);
    cout << "In JurrasicRoad, there weren't any meteorites hitting the Earth 145 million years ago.";
    gotoxy(x - 30, y + 2);
    cout << "Therefore, human and dinosaurs continue to co-exist to present day.";
    gotoxy(x - 30, y + 3);
    cout << "You are a loner stuck in the middle of no where and the only way to get back home";
    gotoxy(x - 30, y + 4);
    cout << "is to cross a bunch of streets filled with cars and dinosaurs.";
    gotoxy(x - 30, y + 5);
    cout << "Your objective is to cross all the roads safely, i.e. not getting hit by anything.";
    gotoxy(x - 30, y + 7);
    cout << "        W";
    gotoxy(x - 30, y + 8);
    cout << "Press A S D to move the character.";
    gotoxy(x - 30, y + 10);
    cout << "Press P to pause the game.";
    gotoxy(x - 30, y + 12);
    system("pause");
    return false;
}

bool InGame::playMenu(int x, int y)
{
    vector<string> options;
    options.push_back("Play");
    options.push_back("Save");
    options.push_back("Settings");
    options.push_back("How to Play");
    options.push_back("Return");
    int choice = menu(x, y, options, "PLAY");
    while (true)
    {
        switch (choice)
        {
        case 0:
            if (gameMenu(x, y))
                continue;
            return true;
        case 1:
            if (saveMenu(x, y))
                continue;
            return true;
        case 2:
            if (settingsMenu(x, y))
                continue;
            return true;
        case 3:
            if (instructionMenu(x, y))
                continue;
            return true;
        case 4:
            return false;
        }
    }
}

bool InGame::loadMenu(int x, int y)
{
    system("cls");
    return loadGame(readDirectory(20, 12), hasSound);
}

bool InGame::settingsMenu(int x, int y)
{
    vector<string> options;
    options.push_back("Sound on");
    options.push_back("Sound off");
    options.push_back("Difficulty");
    options.push_back("Return");
    int choice = menu(x, y, options, "SETTINGS");
    while (true) {
        switch (choice)
        {
        case 0:
            if (!hasSound) {
                hasSound = 1;
                PlaySound(L"background_music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
            return true;
        case 1:
            if (hasSound) {
                hasSound = 0;
                PlaySound(NULL, 0, 0);
            }
            return true;
        case 2:
            if (difficultyMenu(x, y)) continue;
            return true;
        case 3:
            return false;
        }
    }
}

int InGame::menu(int x, int y, vector<string>& options, string menu_name) {
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 15);
    system("cls");
    while (_kbhit()) {
        char a = _getch();
    }
    int choose_num = options.size(), choose = 0;

    for (int i = 0; i < choose_num; ++i)
    {
        gotoxy(x, y + i);
        cout << options[i];
    }

    gotoxy(x - 2, y);
    cout << ">";

    gameTitle(15, 3);
    gotoxy(x - 15, y - 1);
    cout << "------------------------------------------";
    gotoxy(x, y - 1);
    cout << menu_name;
    for (int i = 0; i < choose_num; ++i)
    {
        gotoxy(x - 15, y + i);
        cout << "|";
        gotoxy(x + 26, y + i);
        cout << "|";
    }
    gotoxy(x - 15, y + choose_num);
    cout << "------------------------------------------";
    gotoxy(x - 15, y + choose_num + 2);
    cout << "'W' : Up     'S': Down    'SpaceBar': Select";
    while (1)
    {
        if (_kbhit())
        {
            char getk = _getch();

            if (getk == 'w')
            {
                if (choose == 0) choose = choose_num;
                (--choose) %= choose_num;
            }
            else if (getk == 's')
            {
                (++choose) %= choose_num;
            }
            else if (getk == ' ' || getk == '\n')
            {
                return choose;
            }

            for (int i = 0; i < choose_num; i++)
            {
                gotoxy(x - 2, y + i);
                cout << " ";
            }


            gotoxy(x - 2, y + choose);
            cout << ">";
            gotoxy(0, 0);
        }
    }
}

string InGame::linkBoard(int x = 5, int y = 5)
{
    gotoxy(x, y);
    cout << "enter link to your file: ";
    string str;
    cin >> str;
    return str;
}
void InGame::run()
{
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    changeFont(12, 16);
    ShowConsoleCursor(false);
    //hidecursor();
    while (true)
    {
        if (startMenu(50, 12))
            continue;
        return;
    }
}
