#include "stdafx.h"

#include "SudokuManager.h"
#include "Dispatcher.h"
#include "Timer.h"
#include "TimerFactory.h"

void SudokuManager<bool>::Initialize()
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
		auto temp = (*mySolvers.begin());
		mySolvers.erase(mySolvers.begin());
		delete temp;
	}

	TimerFactory::GetInst()->Initialize();
	Dispatcher<Timer>::GetInst()->Initialize();
}