#include "Game.h"

int main(int argc, char* argv[]) {

	Mode mode;
	bool isGoodInput = true;
	if (argc == 1) // No cmd input
		mode = REGULAR;
	else {

		if (strcmp(argv[1], "-load") == 0)
			mode = LOAD;

		else if (strcmp(argv[1], "-save") == 0)
			mode = SAVE;
		else if (strcmp(argv[1], "-load-silent") == 0)
			mode = SILENT;
		else {
			cout << "Wrong mode input" << endl;
			isGoodInput = false;
		}
	}

	if (isGoodInput) {
		Game g;
		g.printMenu(mode);
	}
	return 0;
}