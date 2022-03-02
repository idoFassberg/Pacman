#pragma once
class Point
{
private:
	int m_Row;
	int m_Col;
	bool m_initializedRow;
	bool m_initializedCol;
public:
	Point(int row = 0, int col = 0) {
		m_Row = row;
		m_Col = col;
		m_initializedRow = m_initializedCol = false;
	}

	//Getters
	int getRow() { return m_Row; }
	int getCol() { return m_Col; }
	bool getInitialized() const { return m_initializedRow && m_initializedCol; }
	bool getInitializedRow() const { return m_initializedRow; }
	bool getInitializedCol() const { return m_initializedCol; }

	//Setters
	void setRow(int Row) { m_Row = Row; }
	void setCol(int Col) { m_Col = Col; }
	void setPoint(int row, int col) {
		m_Row = row;
		m_Col = col;
	}
	void setInitialized(bool flag) { m_initializedRow = m_initializedCol = flag; } //col and row init
	void setInitializedRow(bool flag) { m_initializedRow = flag; }
	void setInitializedCol(bool flag) { m_initializedCol = flag; }
};

