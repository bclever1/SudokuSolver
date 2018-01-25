#pragma once


#include <mutex>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>

#include "Board.h"
#include "Timer.h"
#include "Solver.h"
#include "Macros.h"

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
{
	void operator()(std::shared_ptr<myDataClass<int>> c)
	{
		if (c != nullptr)
		{
			std::cout << c->getData() << std::endl;
		}
	}
};

template <typename W>
class DataManager
{
private:

	static DataManager<W>* myInstance;
	static std::once_flag myOnceFlag;

	std::list<std::unique_ptr<W>> myData;

	std::mutex myMutex;
	bool guessingEnabled;
	bool solutionFound;
	unsigned long numGuesses;
	unsigned long numInvalids;
	unsigned long bestScore;
	unsigned long numSurrenders;
	unsigned long myActiveSolvers;

	DataManager()
	{
		myInstance = this;

		guessingEnabled = false;
		solutionFound = false;
		numGuesses = 0;
		numInvalids = 0;
		bestScore = 0;
		numSurrenders = 0;
		myActiveSolvers = 0;

		if (MY_DEBUG)
		{
			std::ofstream outfile("C:\\TestCases\\sudoku_debug.txt", ios::out);
			outfile << "New run..." << endl;
			outfile.close();
		}
	}

	void ClearData()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (myActiveSolvers == 0)
		{
			int counter = 0;

			while (myData.size() > 0)
			{
				myData.pop_back();
				++counter;
			}

			solutionFound = false;
			bestScore = 10000;
			numGuesses = 0;
			myActiveSolvers = 0;
		}
		else
		{
			std::function<void()> run_callback = std::bind(&DataManager::Run, this);

			myTimerClass tc(run_callback);

			thread* t = new thread(&myTimerClass::timer, tc, 100);
			t->detach();
		}
	}

public:

	static DataManager* GetInst()
	{
		std::call_once(myOnceFlag, []() {new DataManager(); });
		return DataManager::myInstance;
	}

	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	void Initialize()
	{
		std::lock_guard<std::mutex> guard(myMutex);
	}

	void Execute()
	{
		std::lock_guard<std::mutex> guard(myMutex);
        // Set a timer so that main caller can return

		std::function<void()> run_callback = std::bind(&DataManager::Run, this);

		myTimerClass tc(run_callback);

		thread* t = new thread(&myTimerClass::timer, tc, 100);
		t->detach();
	}

	void Run()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (myData.size() > 0)
		{
			for (auto solver = myData.begin();
				solver != myData.end();
				++solver)
			{
				if (myActiveSolvers < 10)
				{
					if ((*solver).get()->GetState() == Solver::SolverState::READY)
					{
						++myActiveSolvers;
						thread* t = new thread(&Solver::Run, solver->get());
						t->detach();
					}
				}
				else
				{
					break;
				}
			}
		}

		std::function<void()> run_callback = std::bind(&DataManager::Run, this);

		myTimerClass tc(run_callback);

		thread* t = new thread(&myTimerClass::timer, tc, 500);
		t->detach();
	}

	void logMessage(std::string theMsg)
	{
		if (MY_DEBUG)
		{
			std::lock_guard<std::mutex> guard(myMutex);
			std::ofstream outfile("C:\\TestCases\\sudoku_debug.txt", ios::app);
			outfile << theMsg << endl;
		}
	}

	void addElement(std::unique_ptr<W> theElement)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (stopped == false)
		{
			myData.push_back(theElement);
			++numGuesses;
		}
	}

	void addElement(Solver* p)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		std::unique_ptr<Solver> P = std::make_unique<Solver>(*p);

		myData.push_back(std::move(P));

		++numGuesses;
	}

	std::unique_ptr<W>& getElementAt(int theIdx)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (theIdx < myData.size())
		{ 
			int idx = 0;
			for (std::list<std::unique_ptr<W>>::iterator itr = myData.begin();
				itr != myData.end();
				++itr, ++idx)
			{
				if (idx == theIdx)
				{
					return (*itr);
				}
			}
		}

		return nullptr;
	}

	std::unique_ptr<W> removeElementAt(int theIdx)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		int idx = 0;
		for (std::list<std::unique_ptr<W>>::iterator itr = myData.begin();
			itr != myData->end();
			++itr, ++idx)
		{
			if (idx == theIdx)
			{
				myData->erase(*itr);
			}
		}
	}

	template <typename T>
	static std::unique_ptr<W> removeElementById(T theId)
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

	void displayAll()
	{
		myDataClassDisplayFunctor f;
		std::for_each(myData->begin(), myData->end(), f);
	}

	void Reset()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		int counter = 0;

		while (myData.size() > 0)
		{
			myData.pop_back();
			++counter;
		}

		solutionFound = false;
		bestScore = 10000;
		numGuesses = 0;
		myActiveSolvers = 0;

	}

	std::unique_ptr<Solver>* GetSolvedBoard()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		for (auto Solver = myData.begin();
			 Solver != myData.end();
			 ++Solver)
		{
			if ((*Solver).get()->GetState() == Solver::SolverState::SOLVED)
			{
				return &(*Solver);
			}
		}

		return nullptr;
	}

	bool GetSolvedYet()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		return solutionFound;
	}

	void SolutionFound(Solver* s)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		solutionFound = true;
	}

	void EnableGuessing()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		guessingEnabled = true;
	}

	void DisableGuessing()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		guessingEnabled = false;
	}

	bool IsGuessingEnabled()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		return guessingEnabled;
	}

	void RegisterCompld(Solver* s)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (s->GetState() == Solver::SolverState::INVALID)
		{
			++numInvalids;
			--myActiveSolvers;
		}
		else if (s->GetState() == Solver::SolverState::SURRENDERED)
		{
			++numSurrenders;
			--myActiveSolvers;
		}
	}

	unsigned long GetNumSurrenders()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		return numSurrenders;
	}

	unsigned long GetNumGuesses()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		return numGuesses;
	}

	unsigned long GetNumInvalids()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		return numInvalids;
	}

	void SetScore(unsigned long myScore)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (myScore < bestScore)
		{
			bestScore = myScore;
		}
	}

	unsigned long GetBestScore()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		return bestScore;
	}
};

template <typename W>
DataManager<W>* DataManager<W>::myInstance = nullptr;

template <typename W>
std::once_flag DataManager<W>::myOnceFlag;
