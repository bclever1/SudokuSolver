#pragma once

#include "Macros.h"
#include <mutex>
#include <fstream>
#include <string>
#include <list>

#include "Board.h"
#include "Solver.h"
#include "TimerFactory.h"

using namespace std;

class SolverFactory
{
private:

	static SolverFactory* my_instance;
	static std::once_flag my_once_flag;
	std::mutex myMutex;
	bool guessingEnabled;
	bool solutionFound;
	uint numGuesses;
	uint numInvalids;
	uint bestScore;
	uint numSurrenders;
	Board mySolvedBoard;
	list<std::unique_ptr<Solver>>mySolvers;

	SolverFactory()
	{
		my_instance = this;
		Initialize();
	}

public:

	static SolverFactory* GetInst()
	{
		std::call_once(SolverFactory::my_once_flag, []() {new SolverFactory(); });
		return SolverFactory::my_instance;
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

	void SolutionFound(std::unique_ptr<Board>* theSolvedBoard)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		solutionFound = true;
		mySolvedBoard = **theSolvedBoard;
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

	void CreateNewSolver(unsigned char theBoard[]);
	void CreateNewSolver(Board& theBoard);
	bool Shutdown();

};