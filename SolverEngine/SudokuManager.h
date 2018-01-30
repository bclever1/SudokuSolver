#pragma once

#include "Macros.h"
#include <mutex>
#include <fstream>
#include <string>
#include <list>

#include "Board.h"
#include "Solver.h"

using namespace std;

template 
<typename T>
class SudokuManager
{
private:

	static SudokuManager* my_instance;
	static std::once_flag my_once_flag;
	std::mutex myMutex;
	bool guessingEnabled;
	bool solutionFound;
	uint numGuesses;
	uint numInvalids;
	uint bestScore;
	uint numSurrenders;
	Board mySolvedBoard;
	list<Solver*>mySolvers;

	SudokuManager()
	{
		my_instance = this;
		Initialize();
	}

public:

	static SudokuManager* GetInst()
	{
		std::call_once(SudokuManager<bool>::my_once_flag, []() {new SudokuManager(); });
		return SudokuManager<bool>::my_instance;
	}

	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	void Initialize();

	void logMessage(std::string theMsg)
	{
		if (MY_DEBUG)
		{
			std::lock_guard<std::mutex> guard(myMutex);
			std::ofstream outfile("C:\\TestCases\\sudoku_debug.txt", ios::app);
			outfile << theMsg << endl;
		}
	}

	bool GetSolvedYet()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		return solutionFound;
	}

	void SolutionFound(Board* theSolvedBoard)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		solutionFound = true;
		mySolvedBoard = *theSolvedBoard;
		TimerFactory::GetInst()->Terminate();
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

	Board* GetSolvedBoard()
	{
		if (solutionFound)
		{
			return &mySolvedBoard;
		}

		return nullptr;
	}

	void RegisterCompld(Solver::SolverState theState)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		if (theState == Solver::SolverState::INVALID) ++numInvalids;
		else if (theState == Solver::SolverState::SURRENDERED) ++numSurrenders;
		else if (theState == Solver::SolverState::INITIALIZING) ++numGuesses;
	}
	
	unsigned long GetActiveSolvers()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (numActiveSolvers == 0)
		{
			if (!solutionFound)
			{
				TimerFactory::GetInst()->Terminate();
			}
		}
		return numActiveSolvers;
	}

	void RegisterNewSolver(Solver* S)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		mySolvers.push_back(S);
		++numGuesses;
	}

	bool Shutdown()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		TimerFactory::GetInst()->Terminate();
		TimerFactory::GetInst()->Initialize();
		Dispatcher<Timer>::GetInst()->Reset();

		while (mySolvers.size() > 0)
		{
			auto temp = (*mySolvers.begin());
			mySolvers.erase(mySolvers.begin());
			delete temp;
		}

		return true;
	}
};

template <typename T>
SudokuManager<T>* SudokuManager<T>::my_instance = nullptr;
template <typename T>
std::once_flag SudokuManager<T>::my_once_flag;
