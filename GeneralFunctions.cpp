#include "GeneralFunctions.h"
using namespace std;

void gotoxy(short x, short y) {

	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { y, x };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);

	hideCursor();
}

void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void hideCursor(){

	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void readFiles(vector<string>& screenFiles){

	using fs = filesystem::directory_iterator;
	for (const auto& file :fs::directory_iterator(".")){

		if (hasEnding(file.path().string(), "screen")){

			screenFiles.push_back(file.path().string());				
		}
	}	
}

bool hasEnding(string fullString, string  ending) {

	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
		return false;	
}