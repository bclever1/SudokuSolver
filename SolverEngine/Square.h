#pragma once

#include <iostream>
#include <vector>

using namespace std;

class displayRegion;
class displayGrid;

class Square
{
	// This class represents one of 81 squares of the sudoku board

public:
	Square(int theRow, int theCol);
	~Square();

	void setValue(int theValue);

	bool contains(int theVal);
	void remove(int theVal);
	void removeAllExcept(int theVal);

	int getValue();
	int getCount();

	bool compareValues(vector<int>& v);
	int getPos(int thePos);

	void copyValues(vector<int>& theValues);
	vector<int> getValues();

	int GetRowNum() { return myRow; }
	int GetColNum() { return myCol; }

private:

	vector<int>* myValues;
	int myRow;
	int myCol;

};