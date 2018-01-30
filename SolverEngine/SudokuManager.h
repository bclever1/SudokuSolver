#pragma once

#include "Macros.h"
#include <mutex>
#include <fstream>
#include <string>

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

	SudokuManager()
	{
		my_instance = this;

		guessingEnabled = true;
		solutionFound = false;
		numGuesses = 0;
		numInvalids = 0;
		bestScore = 100000;
		numSurrenders = 0;
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

	void Initialize()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		guessingEnabled = true;
		solutionFound = false;
		numGuesses = 0;
		numInvalids = 0;
		bestScore = 100000;
		numSurrenders = 0;
		mySolvedBoard.Reset();
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

	void Reset()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		guessingEnabled = true;
		solutionFound = false;
		numGuesses = 0;
		numInvalids = 0;
		bestScore = 100000;
		numSurrenders = 0;
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
		if (theState == Solver::SolverState::INVALID) ++numInvalids;
		else if (theState == Solver::SolverState::SURRENDERED) ++numSurrenders;
		else if (theState == Solver::SolverState::INITIALIZING) ++numGuesses;
	}
};

template <typename T>
SudokuManager<T>* SudokuManager<T>::my_instance = nullptr;
template <typename T>
std::once_flag SudokuManager<T>::my_once_flag;
