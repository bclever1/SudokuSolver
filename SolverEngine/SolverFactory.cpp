#include "stdafx.h"

#include "SolverFactory.h"
#include "Dispatcher.h"
#include "Timer.h"
#include "TimerFactory.h"


SolverFactory* SolverFactory::my_instance = nullptr;
std::once_flag SolverFactory::my_once_flag;

void SolverFactory::Initialize()
{
	std::lock_guard<std::mutex> guard(myMutex);

	guessingEnabled = true;
	solutionFound = false;
	numGuesses = 0;
	numInvalids = 0;
	bestScore = 100000;
	numSurrenders = 0;
	mySolvedBoard.Reset();

	while (mySolvers.size() > 0)
	{
        // My elements are unique_ptrs, so no explicit delete for them!
		mySolvers.erase(mySolvers.begin());
	}

	TimerFactory::GetInst()->Initialize();
	Dispatcher<Timer>::GetInst()->Initialize();
}

void SolverFactory::CreateNewSolver(unsigned char theBoard[])
{
	std::lock_guard<std::mutex> guard(myMutex);

	std::unique_ptr<Solver> newSolver = std::make_unique<Solver>(theBoard);
	mySolvers.push_front(std::move(newSolver));
	(*mySolvers.begin())->Initialize();

	++numGuesses;
}

void SolverFactory::CreateNewSolver(Board& theBoard)
{
	std::lock_guard<std::mutex> guard(myMutex);

	std::unique_ptr<Solver> newSolver = std::make_unique<Solver>(theBoard);
	mySolvers.push_front(std::move(newSolver));
	(*mySolvers.begin())->Initialize();

	++numGuesses;
}

bool SolverFactory::Shutdown()
{
	std::lock_guard<std::mutex> guard(myMutex);
	TimerFactory::GetInst()->Terminate();
	TimerFactory::GetInst()->Initialize();
	Dispatcher<Timer>::GetInst()->Reset();

	while (mySolvers.size() > 0)
	{
		// My elements are unique_ptrs, so no explicit delete for them!
		mySolvers.erase(mySolvers.begin());
	}

	return true;
}