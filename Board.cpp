#include "Board.h"

void Board::printBoard() {

	for (int i = 0; i < m_boardSize.getRow(); i++) {

		for (int j = 0; j < m_boardSize.getCol(); j++) {

			if (m_gameColor == 1) {

				switch (m_board[i][j]) {

				case WALL:
					setTextColor(WHITE);
					break;

				case BREADCRUMB:
					setTextColor(BREADCRUMB_COLOR);
					break;

				case TUNNEL:
					setTextColor(CYAN);
					break;

				case '@':
					setTextColor(PACMAN_COLOR);
					break;

				case '$':
					setTextColor(GHOST_COLOR);
					break;

				default:
					setTextColor(FRUIT_COLOR);
					break;
				}
			}
			cout << m_board[i][j];
		}
		cout << endl;
	}
}

void Board::initBoard(){

	for (int i = 0; i < ROW; i++){

		for (int j = 0; j < COL; j++){
			m_board[i][j] = ' ';
		}
	}
	m_food = 0;
	m_boardSize.setRow(0);
	m_boardSize.setCol(0);
	m_numOfGhosts = 0;
	m_steps.close();
	m_result.close();
	m_boardSize.setInitializedCol(false);
}

void Board::readFromFile(string fileName) {
	ifstream file;
	file.open(fileName);
	string line;

	while (getline(file, line)) {

		if (!m_boardSize.getInitializedCol()) {
			m_boardSize.setCol(line.length());
			m_boardSize.setInitializedCol(true);
		}

		readLineInLenCol(line);

		m_boardSize.setRow(m_boardSize.getRow() + 1);
	}

	for (int i = m_boardSize.getRow(); i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			m_board[i][j] = ' ';
		}
	}

	//clear the spaces from '&'
	for (int i = m_ampPos.getRow(); i < m_ampPos.getRow() + 3; i++) {
		for (int j = m_ampPos.getCol(); j < m_ampPos.getCol() + 20; j++)
			m_board[i][j] = ' ';
	}

	makeTunnels();
	file.close();
}

void Board::makeTunnels() {

	int i, j;
	int horizonTunnelCol = 0;
	//_________________________________________________________________________________
	//run until the first line of the actual game board
	for (i = 0; i < ROW; i++) {
		if (m_board[i][0] == WALL)
			break;
	}
	// i is now the first board line
	for (j = 0; j < COL; j++) {

		if (m_board[i][j] == BREADCRUMB) {

			m_board[i][j] = TUNNEL;
			m_food--;
			horizonTunnelCol = j;
			break;
		}
	}

	for (j = ROW - 1; j > 0; j--) {

		if (m_board[j][horizonTunnelCol] == BREADCRUMB) {

			m_board[j][horizonTunnelCol] = TUNNEL;
			m_food--;
			break;
		}
	}
	//_________________________________________________________________________________
	//run until the first col of the actual board
	int verticalTunnelRow;

	for (i = 0; i < COL; i++) {
		if (m_board[0][i] == WALL)
			break;
	}

	for (j = i; j < ROW; j++) {

		if (m_board[j][0] == BREADCRUMB) {

			m_board[j][0] = TUNNEL;
			m_food--;
			verticalTunnelRow = j;
			break;
		}
	}

	for (i = COL - 1; i > 0; i--) {

		if (m_board[verticalTunnelRow][i] == BREADCRUMB) {

			m_board[verticalTunnelRow][i] = TUNNEL;
			m_food--;
			break;
		}
	}
}

void Board::readLineInLenCol(string line) {

	bool isLongerThanCol = false, isAmpFound = false, isFirstLine = true;
	int len = line.length();

	int i = 0;

	if (len > m_boardSize.getCol()) {
		m_boardSize.setInitializedCol(false);
		throw LongerLineThanFirstOne();
	}

	while (line[i] != '\0') {

		switch (line[i]) {

		case ' ':
			m_board[m_boardSize.getRow()][i] = BREADCRUMB;
			m_food++;
			break;

		case '%':
			m_board[m_boardSize.getRow()][i] = ' ';
			break;

		case '&':
			if (m_pacmanFirstPos.getInitialized()) // we already saw a '&'
				throw MoreThanOneAmp();
			m_board[m_boardSize.getRow()][i] = '&';
			m_ampPos.setPoint(m_boardSize.getRow(), i);
			m_ampPos.setInitialized(true);
			break;

		case '@':
			if (m_pacmanFirstPos.getInitialized()) // we already saw a pacman
				throw MoreThanOnePacman();
			m_board[m_boardSize.getRow()][i] = '@';
			m_pacmanFirstPos.setPoint(m_boardSize.getRow(), i);
			m_pacmanFirstPos.setInitialized(true);
			break;

		case '$':
			m_board[m_boardSize.getRow()][i] = '$';
			if (m_numOfGhosts > 4) {
				throw MoreThanFourGhosts();
			}
			m_ghostFirstPos[m_numOfGhosts++].setPoint(m_boardSize.getRow(), i);
			break;

		default: // takes care if sees '&' not after the board log size
			m_board[m_boardSize.getRow()][i] = line[i];
		}
		i++;
	}

	for (i = 0; i < COL; i++) {
		m_board[m_boardSize.getRow()][m_boardSize.getCol() + i] = ' ';
	}
}

void Board::openFile(string Name, Mode mode) {

	string stepsFileString = Name.substr(0, 11);
	stepsFileString += ".steps";
	if (mode == SAVE)
		m_steps.open(stepsFileString, ios::out);

	else if(mode==LOAD || mode== SILENT){
		m_steps.open(stepsFileString, ios::in);
	}
	string resultFileString = Name.substr(0, 11);
	resultFileString += ".result";
	if (mode == SAVE)
		m_result.open(resultFileString, ios::out);
	else if (mode == LOAD || mode == SILENT)
	{
		m_result.open(resultFileString, ios::in);
	}
}