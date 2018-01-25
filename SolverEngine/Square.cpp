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
#if 0
	while (myValues.size() > 0)
	{
		myValues.pop_back();
	}

	myValues.shrink_to_fit();
#endif

}

bool Square::contains(int theval)
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (myValues[theval] == 1) return true;
	return false;

#if 0
	for (std::vector<int>::iterator itr = myValues.begin();
		itr != myValues.end();
		++itr)
	{
		if (*itr == theval)
		{
			return true;
		}
	}
#endif

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

#if 0
	for (std::vector<int>::iterator itr = myValues.begin();
		itr != myValues.end();
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

			myValues.erase(itr);
			return;
		}
	}
#endif

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

#if 0
	bool found = false;
	for (std::vector<int>::iterator itr = myValues.begin();
		itr != myValues.end();
		++itr)
	{
		if (*itr == theval)
		{
			found = true;
			break;
		}
	}

	if (found == false) return;

	while (myValues.size() > 1)
	{
		for (std::vector<int>::iterator itr = myValues.begin();
			itr != myValues.end();
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

				myValues.erase(itr);
				break;
			}
		}
	}
#endif

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
