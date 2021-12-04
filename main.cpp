#include "Header.h"

int main() {
	srand(time(NULL));
	ios::sync_with_stdio(0);
	loadCharacters();
	InGame menu;
	menu.run();
}
