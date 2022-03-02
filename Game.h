#pragma once
#include "pacman.h"
#include "BestGhost.h"
#include "GoodGhost.h"
#include "NoviceGhost.h"
#include "Fruit.h"

const int SPEED = 60;

class Game {

private:

	char m_currentCh;
	Board m_board;
	Pacman m_pacman;
	Ghost* m_ghostArr[4];
	Fruit m_fruit;
	char m_level;
	Mode m_mode;
	vector<string> m_screenList;
	bool m_isReadFile = false;
	bool m_isWon = true;
	int TimeCounter = 0;
    bool m_AllScreens;
public:

	//Constractors
	Game();

	//Functions
	void printMenu(Mode mode);
	void startGame();
	bool isWin();
	void waitForKey();
	void gameOver();
	bool presentKeys();
	void gamePause();
	void updateKey();
	void printWin();
	bool isValidKey(char ch);
	void gameColor();
	void initAll();
	void chooseLevel();
	void initGhostArr();
	void initCreaturesOnScreen();
	void chooseFile();
	void speed();
	void TranslatePacmanFirstMove();
	void silentPrint(bool silentTest);
	void setModeForBoard() { m_board.setMode(m_mode); }
};