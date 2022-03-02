#pragma once

#include "GeneralFunctions.h"
#include "Point.h"
#include <fstream>
#include <sstream>
#include "MoreThanFourGhosts.h"
#include "MoreThanOnePacman.h"
#include "MoreThanOneAmp.h"
#include "LongerLineThanFirstOne.h"

const int ROW = 25; //max rows possible for a valid board
const int COL = 80; //max cols possible for a valid board

const char BREADCRUMB = '.';
const char WALL = '#';
const char TUNNEL = 'O';

const Color PACMAN_COLOR = YELLOW;
const Color GHOST_COLOR = RED;
const Color BREADCRUMB_COLOR = BLUE;
const Color FRUIT_COLOR = GREEN;

class Board {


private:
	char m_board[ROW][COL];
	int m_food = 0;
	int m_gameColor = 0;
	Point m_boardSize;

	Point m_ampPos;
	Point m_ghostFirstPos[4];
	int m_numOfGhosts = 0;

	Point m_pacmanPos; //for connection between class Ghost to Pacman position
	Point m_pacmanFirstPos;
	char m_charUnderFruit = BREADCRUMB;
	fstream m_steps;
	fstream m_result;
	Mode m_mode;

public:

	//Functions
	void printBoard();
	void initBoard();
	void readFromFile(string fileName);
	void readLineInLenCol(string line);
	void makeTunnels();
	void openFile(string Name,Mode mode);

	//Getters
	Point getPacmanPos() const { return m_pacmanPos; }
	Point getPacmanFirstPos() const { return m_pacmanFirstPos; }
	Point getAmpPos() const { return m_ampPos; }
	int getReaminFood() { return m_food; }
	int getGameColor()  const { return m_gameColor; }
	int getNumOfGhosts() const { return m_numOfGhosts; }
	char getCharOnBoard(int row, int col) const { return m_board[row][col]; }
	char getCharUnderFruit() const { return m_charUnderFruit; }
	Point* getGhostsPos() { return m_ghostFirstPos; }
	Point getBoardSize() const { return m_boardSize; }
	fstream& getStepsFile() { return m_steps; }
	fstream& getResultFile() { return m_result; }
	Mode getMode() const { return m_mode; }

	//Setters
	void setGameColor(const int gameColor) { m_gameColor = gameColor; }
	void setCharOnBoard(char ch, int row, int col) { m_board[row][col] = ch; }
	void setCharUnderFruit(char ch) { m_charUnderFruit = ch; }
	void setRemainFood() { m_food--; }
	void setPacmanPos(int r, int c) { m_pacmanPos.setPoint(r, c); }
	void setPacmanUninitialized() { m_pacmanFirstPos.setInitialized(false); }
	void setAmpUninitialized() { m_ampPos.setInitialized(false); }
	void setMode(Mode mode) { m_mode = mode; }
};