#pragma once


#include <mutex>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <string>

#include "Board.h"

#define MY_DEBUG true

template <typename T>
class myDataClass
{
public:
	myDataClass(T theData)
	{
		myData = theData;
	}
	~myDataClass() {}

	T getData() { return myData; }

private:
	T myData;
};

struct myDataClassDisplayFunctor

	static void addElement(std::shared_ptr<W> theElement)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		myData->push_back(theElement);
	}

	static std::shared_ptr<W> getElementAt(int theIdx)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (theIdx < myData->size())
		{
			return (*myData)[theIdx];
		}

		return nullptr;
	}

	static std::shared_ptr<W> removeElementAt(int theIdx)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		std::vector<std::shared_ptr<W>>::iterator itr;

		int myIdx = 0;
		for (itr = myData->begin(), myIdx = 0; myIdx <= theIdx; ++itr, ++myIdx)
		{
			if (myIdx == theIdx)
			{
				std::shared_ptr<W> temp = *itr;
				myData->erase(itr);
				return temp;
			}
		}

		return nullptr;
	}

	template <typename T>
	static std::shared_ptr<W> removeElementById(T theId)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		std::vector<std::shared_ptr<W>>::iterator itr;

		for (itr = myData->begin(); itr != myData->end(); ++itr)
		{
			if ((*itr)->getData() == theId)
			{
				std::shared_ptr<W> temp = *itr;
				myData->erase(itr);
				return temp;
			}
		}

		return nullptr;
	}

	static void displayAll()
	{
		myDataClassDisplayFunctor f;
		std::for_each(myData->begin(), myData->end(), f);
	}

	static void Reset()
	{
		myData->clear();
		mySpecialData = nullptr;
	}

	static std::shared_ptr<Board> GetSolvedBoard()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (mySpecialData != nullptr)
		{
			return mySpecialData.get()->GetBoardPtr();
		}

		return nullptr;
	}

	static bool GetSolvedYet()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		if (mySpecialData != nullptr)
		{
			return true;
		}

		return false;
	}

	static void SolutionFound(std::shared_ptr<W> theW)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		mySpecialData = theW;
	}

	static void EnableGuessing()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		guessingEnabled = true;
	}

	static void DisableGuessing()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		guessingEnabled = false;
	}

	static bool IsGuessingEnabled()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		return guessingEnabled;
	}

private:

	DataManager()
	{
		myInstance = this;
		DataManager::myData = new std::vector<std::shared_ptr<W>>();
		std::ofstream outfile("C:\\TestCases\\sudoku_debug.txt", ios::out);
		outfile << "New run..." << endl;
		outfile.close();
	}

	static DataManager<W>* myInstance;
	static std::vector<std::shared_ptr<W>>* myData;
	static std::once_flag myOnceFlag;
	static std::mutex myMutex;
	static std::shared_ptr<W> mySpecialData;
	static bool guessingEnabled;
};


template <typename W>
std::once_flag DataManager<W>::myOnceFlag;

template <typename W>
std::mutex DataManager<W>::myMutex;

template <typename W>
DataManager<W>* DataManager<W>::myInstance = nullptr;

template <typename W>
std::vector<std::shared_ptr<W>>* DataManager<W>::myData = nullptr;

template <typename W>
std::shared_ptr<W> DataManager<W>::mySpecialData = nullptr;

template <typename W>
bool DataManager<W>::guessingEnabled = false;
