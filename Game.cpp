#include "Game.h"

void Game::printMenu(Mode mode) {

	m_mode = mode;
	setModeForBoard();
	bool isGoodBoard = true;

	if (m_mode == LOAD || m_mode == SILENT) {
		if (!m_isReadFile) {

			readFiles(m_screenList);
			m_isReadFile = true;
		}

		system("cls");
		m_isWon = true;

		int gameCounter = 0;
		while (m_screenList.size() != 0 && m_isWon) {

			m_isWon = false;
			m_board.openFile(m_screenList[0], m_mode);
			if (gameCounter == 0)
			{
				int tmpGameColor;
				m_board.getStepsFile() >> tmpGameColor; //read from file
				m_pacman.getBoard().setGameColor(tmpGameColor);
				m_board.getStepsFile() >> m_level;
			}
			try {
				m_board.readFromFile(m_screenList[0]);
			}
			catch (Error& e) {
				cout << "ERROR: " << e.getMsg() << endl <<
					"Lets try your next board if there is one!" << endl;
				isGoodBoard = false;
			}
			
			if (isGoodBoard)
			{
				gameCounter++;
				startGame();
			}
			m_screenList.erase(m_screenList.begin());
		}
		if (m_isWon) {

			system("cls");
			gotoxy(14, 35);
			cout << "CONGRATULATIONS! YOU WIN! There are no more screens to beat";
			gotoxy(15, 35);
			cout << "Press any key to exit";

			char tmp;
			tmp = _getch();		
		}
		return;
	}
	
	int choice;
	bool wantToPlay = true;

	srand(time(NULL));

	while (wantToPlay) {

		system("cls");
		gotoxy(0, 0);
		setTextColor(WHITE);
		cout << "(1) Start a New Game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;

		cin >> choice;
		while (choice != 1 && choice != 8 && choice != 9) {

			cout << "Invalid input, Please try again!" << endl;
			cin >> choice;
		}

		switch (choice) {

		case 1:
			gameColor(); // Choose the game color
			chooseLevel();

			if (!m_isReadFile) {

				readFiles(m_screenList);
				m_isReadFile = true;
			}

			chooseFile();
			system("cls");
			m_isWon = true;

			if (m_AllScreens) { //all screens

				int gameCounter = 0;
				while (m_screenList.size() != 0 && m_isWon) {

					m_isWon = false;
					m_board.openFile(m_screenList[0],m_mode);
					if (gameCounter == 0) {
						m_board.getStepsFile() << m_board.getGameColor() << " ";
						m_board.getStepsFile() << m_level << " ";
					}
					try {
						m_board.readFromFile(m_screenList[0]);
					}
					catch (Error& e) {
						cout << "ERROR: " << e.getMsg() << endl <<
							"Lets try your next board if there is one!" << endl;
						char tmp;
						tmp = _getch();
						isGoodBoard = false;
					}

					if (isGoodBoard){
						gameCounter++;
						startGame();
					}					
					else {
						m_isWon = true;
						isGoodBoard = true;
						m_board.initBoard();
					}

					m_screenList.erase(m_screenList.begin());
				}

				if (m_isWon) {

					system("cls");
					gotoxy(14, 35);
					cout << "CONGRATULATIONS! YOU WIN! There are no more screens to beat";
					gotoxy(15, 35);
					cout << "Press any key to exit";

					char tmp;
					tmp = _getch();
				}
				for (int i = 0; i < m_screenList.size(); i = i)
					m_screenList.erase(m_screenList.begin());

				readFiles(m_screenList);			
			}
			else {  // specific scrren
				string whichFile;

				cout << "Please enter File name (Type " << "./ " << "and than the name of the file and than " << " .screen)" << endl;
				bool isFoundName = false;
				cin.ignore();
				while (!isFoundName) {

					getline(cin, whichFile);
					for (int i = 0; i < m_screenList.size(); i++) {

						if (whichFile == m_screenList[i]) {

							isFoundName = true;
							try {
								m_board.readFromFile(m_screenList[i]);
							}
							catch (Error& e) {
								cout << "ERROR: " << e.getMsg() << endl <<
									"You chose a specific file so can't move to the next board." << endl <<
									"Please fix your board and try again later!" << endl;
								char tmp;
								tmp = _getch();
								return;
							}
						}
					}
					if (!isFoundName)
						cout << "This File Does not exist, Please try again" << endl;
				}
				startGame();
				m_pacman.initRemainLife();
			}
			break;

		case 8:
			wantToPlay = presentKeys();
			break;

		case 9:
			wantToPlay = false;
			break;
		}
		if (!wantToPlay) {
			system("cls");
			cout << "Bye Bye !" << endl;
		}
	}
}

void Game::chooseLevel() {

	char tmpLevel;
	system("cls");
	cout << "(a) BEST" << endl;
	cout << "(b) GOOD" << endl;
	cout << "(c) NOVICE" << endl;
	cin >> tmpLevel;

	while (tmpLevel != 'a' && tmpLevel != 'b' && tmpLevel != 'c') {
		cout << "Invalid input, Please try again!" << endl;
		cin >> tmpLevel;
	}
	m_level = tmpLevel;
}

void Game::gameColor() {

	int tmpGameColor;

	system("cls");
	cout << "(0) Black and White Game" << endl;
	cout << "(1) Game With Colors" << endl;
	cin >> tmpGameColor;

	while (tmpGameColor != 0 && tmpGameColor != 1) {
		cout << "Invalid input, Please try again!" << endl;
		cin >> tmpGameColor;
	}

	m_pacman.getBoard().setGameColor(tmpGameColor);
}

bool Game::presentKeys() {

	char choice;

	system("cls");
	cout << "Here are the keys for playing Pacman: " << endl;
	cout << " UP    - w \n DOWN  - x \n RIGHT - d \n LEFT  - a \n STAY  - s \n PAUSE - esc \n" << endl;
	cout << " Press 0 to return to main menu. \n Press any other number to EXIT. " << endl;

	cin >> choice;

	if (choice != '0') // 0 is 0 in ASCII table
		return false;
	return true;
}

bool Game::isValidKey(char ch) {

	if (ch == 'w' || ch == 'W' || ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D' ||
		ch == 'x' || ch == 'X' || ch == 's' || ch == 'S')
		return true;
	else
		return false;
}

void Game::startGame() {
	
	initGhostArr();
	bool gamePaused = false, silentTest = true;
	bool win = false, lose = false;
	initCreaturesOnScreen();

	waitForKey();// waits only in regular and save mode

	if (m_mode == SAVE)
		TranslatePacmanFirstMove();
	if (m_mode == LOAD || m_mode == SILENT){

		int temp;
		m_board.getStepsFile() >> temp;
		m_pacman.setDir((Direction)temp);
	}


	while (!win || !lose) {

		while (!_kbhit()) {

			if (gamePaused) { // will go inside only in REGULAR or SAVE mode
				gotoxy(0, 0);
				m_pacman.getBoard().printBoard();
				gamePaused = false;
			}
			TimeCounter++;
			updateKey(); //for moving pacman

			//_____________________________________pacman section_____________________________________

			if (m_pacman.getDir() != STAY) {
				if (m_pacman.move(m_mode)) { // if Pacman encountered ghost OR fruit

					if ((m_pacman.getRow() == m_fruit.getRow()) &&
						(m_pacman.getCol() == m_fruit.getCol())) { //pacman encounter fruit

						m_pacman.setPoints(m_fruit.getScore() - '0');
						m_fruit.setIsOnBoardFalse();
					}
					else { //pacman encounter ghost

						for (int j = 0; j < m_pacman.getBoard().getNumOfGhosts(); j++)
							m_ghostArr[j]->reset(j,m_mode);
						if (m_mode == SAVE)
							m_board.getResultFile() << TimeCounter << " ";
						if (m_mode == SILENT)
						{
							int temp;
							m_board.getResultFile() >> temp;
							if (temp != TimeCounter)
								silentTest = false;
						}
						waitForKey();
					}
				}
			}

			//_____________________________________fruit section_____________________________________
			if (m_fruit.move(m_mode)) {
				m_pacman.setPoints(m_fruit.getScore() - '0');
			}
			//_____________________________________ghost section_____________________________________
			for (int j = 0; j < m_board.getNumOfGhosts(); j++) {

				if (m_ghostArr[j]->move(m_mode)) {// ghost encounter pacman OR fruit

					if ((m_ghostArr[j]->getRow() == m_fruit.getRow()) && (m_ghostArr[j]->getCol() == m_fruit.getCol())) { // fruit

						m_fruit.setIsOnBoardFalse();
					}
					else { // encounter pacman

						for (int j = 0; j < m_pacman.getBoard().getNumOfGhosts(); j++)
							m_ghostArr[j]->reset(j,m_mode);
						m_pacman.init(m_mode);
						m_pacman.setRemainLife();
						m_pacman.printPointsAndRemainLife();
						if (m_mode == SAVE)
							m_board.getResultFile() << TimeCounter << " ";
						if (m_mode == SILENT)
						{
							int temp;
							m_board.getResultFile() >> temp;
							if (temp != TimeCounter)
								silentTest = false;
						}
						waitForKey();
					}
				}
			}
			speed();

			m_pacman.printPointsAndRemainLife();

			if (isWin() || m_pacman.isLose())
				break;
		}

		if (isWin()) {
			if (m_mode == SILENT)
			{
				int temp;
				m_board.getResultFile() >> temp;
				if (temp != TimeCounter)
					silentTest = false;
			}
			m_isWon = true;
			printWin();
			win = true;
			break;
		}
		if (m_pacman.isLose()) {
			if (m_mode != SILENT)
				gameOver();
			lose = true;
			break;
		}

		m_currentCh = _getch();

		if (m_currentCh == 27 && (m_mode == REGULAR || m_mode == SAVE)) { // ESC
			gamePause();
			gamePaused = true;
		}
	}
	silentPrint(silentTest);
	initAll();
}

void Game::silentPrint(bool silentTest) {

	if (m_mode == SAVE)
		m_board.getResultFile() << TimeCounter << " ";

	if (m_mode != SILENT)
		return;

	if (silentTest)
		cout << "Test Passed for " << m_screenList[0] << "!"<< endl;
	else
		cout << "Test Failed!" << m_screenList[0] << "!"  << endl;

	cout << "Please enet any key to continue the tests!" << endl;
	char tmp;
	tmp = _getch();
}

void Game::speed() {

	switch (m_mode) {

	case SAVE: case REGULAR:
		Sleep(SPEED);
		break;

	case LOAD:
		Sleep(SPEED / 2);
		break;

	case SILENT:
		//do nothing
		break;
	}
}

void Game::initGhostArr() {

	for (int i = 0; i < m_board.getNumOfGhosts(); i++) {

		switch (m_level) {

		case 'a': // BEST
			m_ghostArr[i] = new BestGhost(m_board);
			break;

		case 'b': // GOOD
			m_ghostArr[i] = new GoodGhost(m_board);
			break;

		case 'c': // NOVICE
			m_ghostArr[i] = new NoviceGhost(m_board);
			break;
		}
		//No option for another letter cause we continue only
		//afer selecting a VALID letter
	}
}

void Game::initCreaturesOnScreen() {

	system("cls");
	_flushall();
	if (m_mode != SILENT) {
		m_pacman.getBoard().printBoard();
		m_pacman.printPointsAndRemainLife();
	}
	for (int j = 0; j < m_pacman.getBoard().getNumOfGhosts(); j++)
		m_ghostArr[j]->initGhost(j,m_mode);

	m_pacman.init(m_mode);
	m_fruit.init(m_mode);

	if (m_mode == SILENT)
		return;
	gotoxy(m_fruit.getRow(), m_fruit.getCol());
	m_board.setCharOnBoard(m_fruit.getScore(), m_fruit.getRow(), m_fruit.getCol());
	if (m_board.getGameColor())
		setTextColor(FRUIT_COLOR);
	cout << m_fruit.getScore();
}

void Game::chooseFile() {

	system("cls");

	cout << "choose if you want a specific screen or trying to beat all screens" << endl;

	cout << "(0) - specific Screen" << endl;
	cout << "(1) - All screens" << endl;
	int tmp;
	
	do {
		cin >> tmp;
		if(tmp != 0 && tmp != 1)
			cout << "Invalid input, Please try again!" << endl;
	} while (tmp != 0 && tmp != 1);

	m_AllScreens = (bool)tmp;
}

void Game::waitForKey() {

	if (m_mode == REGULAR || m_mode == SAVE) {

		if (!m_pacman.isLose()) { // Do NOT need for the player to insert a key after loosing

			do { //Wait until user press a move key to start again
				m_currentCh = _getch();
			} while (!isValidKey(m_currentCh));
		}
	}
}

void Game::initAll() {

	m_pacman.setPoints(-m_pacman.getPoints());

	if (!m_isWon)
		m_pacman.initRemainLife();

	for (int i = 0; i < m_board.getNumOfGhosts(); i++)
		delete m_ghostArr[i];

	m_board.initBoard();

	system("cls");

	m_board.setPacmanUninitialized();
	m_board.setAmpUninitialized();
	m_board.setCharUnderFruit('.');	

	TimeCounter = 0;
	_flushall();
}

void Game::printWin() {

	if (m_mode == SAVE || m_mode == REGULAR){

		system("cls");
		gotoxy(14, 35);
		cout << "CONGRATULATIONS! YOU WIN!";
		gotoxy(15, 35);
		if(m_AllScreens)
			cout << "Press any key to go to next stage."; 
		else
			cout << "Press any key to go back to main menu";
		char tmp;
		tmp = _getch();
	}
}

void Game::gamePause() {

	gotoxy(5, 20);

	for (int i = 0; i < m_board.getBoardSize().getRow() / 2; i++) {

		gotoxy(5 + i, 20);

		for (int j = 0; j < m_board.getBoardSize().getCol() / 2; j++)
			cout << ' ';
	}

	gotoxy((m_board.getBoardSize().getRow() / 2) + 2, (m_board.getBoardSize().getCol() / 2) + 2);
	cout << "GAME PAUSED!";

	do {
		m_currentCh = _getch();
	} while (m_currentCh != 27);
}

void Game::updateKey() {

	if (m_mode == SAVE || m_mode == REGULAR) {

		switch (m_currentCh) {

		case 'a': case 'A':
			m_pacman.setDir((Direction)LEFT);
			break;

		case 'w': case 'W':
			m_pacman.setDir((Direction)UP);
			break;
		case 'd': case 'D':
			m_pacman.setDir((Direction)RIGHT);
			break;
		case 'x': case 'X':
			m_pacman.setDir((Direction)DOWN);
			break;

		case 's': case 'S':
			m_pacman.setDir((Direction)STAY);
			break;
		}

		if (m_mode == SAVE){
			m_board.getStepsFile() << m_pacman.getDir() << " ";
		}
	}
	else { // SILENT or LOAD
		int temp;
		m_board.getStepsFile() >> temp;
		m_pacman.setDir(Direction(temp));
	}
}

bool Game::isWin() {

	if (m_board.getReaminFood() == 0) {
		m_isWon = true;
		return true;
	}
	return false;
}

void Game::gameOver() {

	system("cls");
	gotoxy(9, 35);
	cout << "GAME OVER!";
	gotoxy(10, 35);
	cout << "Press any key to go back to main menu.";

	char tmp;
	tmp = _getch();
}

Game::Game() : m_pacman(m_board), m_fruit(m_board) {

	m_currentCh = 'v';
	
}

void Game :: TranslatePacmanFirstMove(){

	switch (m_currentCh) {

	case 'a': case 'A':
		m_board.getStepsFile() << ((Direction)LEFT) << " ";
		break;
	case 'w': case 'W':
		m_board.getStepsFile() << ((Direction)UP) << " ";
		break;
	case 'd': case 'D':
		m_board.getStepsFile() << ((Direction)RIGHT) << " ";
		break;
	case 'x': case 'X':
		m_board.getStepsFile() << ((Direction)DOWN) << " ";
		break;
	}
}