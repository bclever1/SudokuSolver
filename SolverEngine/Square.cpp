#include "stdafx.h"
#include "Square.h"
#include <memory>
#include <string>
#include "DataManager.h"
#include "SolverPair.h"

Square::Square(int theRow, int theCol) : myRow(theRow), myCol(theCol)
{
	myValues = new vector<int>({ 1,2,3,4,5,6,7,8,9 });
}

Square::~Square()
{
	myValues->clear();
	delete myValues;
}

bool Square::contains(int theval)
{
	for (std::vector<int>::iterator itr = myValues->begin();
		itr != myValues->end();
		++itr)

	{
		if (*itr == theval)
		{
			return true;
		}
	}

	return false;
}


void Square::remove(int theval)
{
	for (std::vector<int>::iterator itr = myValues->begin();
		itr != myValues->end();
		++itr)
	{
		if (*itr == theval)
		{
			if (1)
			{
			    std::string s = "    Removing: " +  std::to_string(theval) + " from Square: (" \
				                +  std::to_string(myRow) + "," + std::to_string(myCol) + ")\n";
				DataManager<SolverPair>::GetInst()->logMessage(s);
			}

			myValues->erase(itr);
			return;
		}
	}
}


void Square::removeAllExcept(int theval)
{
	// First make sure I contain the specified value

	bool found = false;
	for (std::vector<int>::iterator itr = myValues->begin();
		itr != myValues->end();
		++itr)
	{
		if (*itr == theval)
		{
			found = true;
			break;
		}
	}

	if (found == false) return;

	while (myValues->size() > 1)
	{
		for (std::vector<int>::iterator itr = myValues->begin();
			itr != myValues->end();
			++itr)
		{
			if (*itr != theval)
			{
				if (1)
				{
				    std::string s = "    Removing: " + std::to_string(theval) + " from Square: (" \
					               + std::to_string(myRow) + "," + std::to_string(myCol) + ")\n";
					DataManager<SolverPair>::GetInst()->logMessage(s);
				}

				myValues->erase(itr);
				break;
			}
		}
	}
}


void Square::setValue(int theValue)
{
	if (theValue != 0)
	{
		myValues->clear();
		myValues->push_back(theValue);
	}
}


int Square::getValue()
{
	int theResult = 0;
	for (vector<int>::iterator itr = myValues->begin();
		itr != myValues->end();
		++itr)
	{
		theResult += (*itr);
	}

	return theResult;
}


int Square::getCount()
{
	return myValues->size();
}

bool Square::compareValues(vector<int>& v)
{
	if ((*myValues) == v) return true;
	return false;
}

int Square::getPos(int thePos)
{
	return (*myValues)[thePos];
}

void Square::copyValues(vector<int>& v)
{
	myValues->clear();

	for (int i = 0; i < v.size(); ++i)
	{
		myValues->push_back((v)[i]);
	}
}
vector<int> Square::getValues()
{
	return *myValues;
}
