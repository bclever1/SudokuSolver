#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <bitset>

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

	bool compareValues(bitset<10>& v);
	int getSingleton();

	void copyValues(bitset<10>& v);
	bitset<10>& getValues();

	int GetRowNum() { return myRow; }
	int GetColNum() { return myCol; }

	static std::bitset<10>zero;
	static std::bitset<10>one;
	static std::bitset<10>two;
	static std::bitset<10>three;
	static std::bitset<10>four;
	static std::bitset<10>five;
	static std::bitset<10>six;
	static std::bitset<10>seven;
	static std::bitset<10>eight;
	static std::bitset<10>nine;

private:

	//vector<int> myValues;
	std::bitset<10> myValues;
	
	std::mutex myMutex;
	int myRow;
	int myCol;

};