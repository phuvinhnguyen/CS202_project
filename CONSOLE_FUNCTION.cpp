#include "Header.h"

void gotoxy(OXY coord) {
    gotoxy(coord.x, coord.y);
}

void gotoxy(int x, int y) {
    static HANDLE h = nullptr;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void playSound(const wchar_t* file) {
    // PlaySound(file, NULL, SND_ASYNC | SND_FILENAME);
}

void FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void changeFont(int W, int H) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = W;
    cfi.dwFontSize.Y = H;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Monospace");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void SetWindowSize(SHORT width, SHORT height) {
    COORD ScreenBufferSize{ 1500, 300 };
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND ConsoleWindow = GetConsoleWindow();

    SetConsoleScreenBufferSize(ConsoleHandle, ScreenBufferSize);
    ShowWindow(ConsoleWindow, SW_MAXIMIZE);
}