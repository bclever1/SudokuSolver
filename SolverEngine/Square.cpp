#include "stdafx.h"
#include "Square.h"
#include <memory>
#include <string>
#include "DataManager.h"
#include "SolverPair.h"


Square::Square(int theRow, int theCol) : myRow(theRow), myCol(theCol)
{
	for (int i = 1; i <= 9; ++i)
	{
		myValues[i] = 1;
	}
}

Square::~Square()
{
}

bool Square::contains(int theval)
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (myValues[theval] == 1) return true;
	return false;
}


void Square::remove(int theval)
{
	std::lock_guard<std::mutex> guard(myMutex);

	int theResult = 0;

	for (int i = 1; i <= 9; ++i)
	{
		if (myValues[i] == 1)
		{
			theResult += 1;
		}
	}

	if (theResult > 1)
	{
		myValues[theval] = 0;
	}
}


void Square::removeAllExcept(int theval)
{
	// First make sure I contain the specified value

	std::lock_guard<std::mutex> guard(myMutex);

	if (myValues[theval] == 1)
	{
		for (int i = 1; i <= 9; ++i)
		{
			if (i != theval)
			{
				myValues[i] = 0;
			}
		}
	}
}


void Square::setValue(int theval)
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (theval != 0)
	{
		for (int i = 1; i <= 9; ++i)
		{
			myValues[i] = 0;
		}
		myValues[theval] = 1;
	}
}


int Square::getValue()
{
	std::lock_guard<std::mutex> guard(myMutex);
	int theResult = 0;

	for (int i = 1; i <= 9; ++i)
	{
		if (myValues[i] == 1)
		{
			theResult += i;
		}
	}

	return theResult;
}


int Square::getCount()
{
	std::lock_guard<std::mutex> guard(myMutex);
	int theResult = 0;

	for (int i = 1; i <= 9; ++i)
	{
		if (myValues[i] == 1)
		{
			theResult += 1;
		}
	}

	return theResult;
}

bool Square::compareValues(bitset<10>& v)
{
	std::lock_guard<std::mutex> guard(myMutex);

	for (int i = 1; i <= 9; ++i)
	{
		if (myValues[i] != v[i])
		{
			return false;
		}
	}

	return false;
}

int Square::getSingleton()
{
	std::lock_guard<std::mutex> guard(myMutex);

	for (int i = 1; i <=9; ++i)
	{
		if (myValues[i] == 1)
		{
			return i;
		}
	}
	return 0;
}

void Square::copyValues(bitset<10>& v)
{
	std::lock_guard<std::mutex> guard(myMutex);
	
	for (int i = 1; i <= 9; ++i)
	{
		myValues[i] = v[i];
	}
}
bitset<10>& Square::getValues()
{
	std::lock_guard<std::mutex> guard(myMutex);
	return myValues;
}
