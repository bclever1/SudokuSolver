#include "stdafx.h"
#include "Solver.h"
#include "Board.h"
#include "DataManager.h"

#include <thread>
#include <time.h>

void Solver::Run()
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (mySolverState == SolverState::READY)
	{
		mySolverState = SolverState::RUNNING;
	}

	if (!(myBoard->CheckValid()))
	{
		// I was created invalid. Bummer.
		mySolverState = SolverState::INVALID;
		DataManager<Solver>::GetInst()->RegisterCompld(this);
		return;
	}

	if (DataManager<Solver>::GetInst()->GetSolvedYet())
	{
		mySolverState = SolverState::SURRENDERED;
		return;
	}

	int myBoardState = myBoard->GetBoardState();

	// Do the obvious reductions of the rows, columns and blocks
	for (int theItem = 1; theItem <= 9; ++theItem)
	{
		Reduce(Board::SquareGroupType_e::Row, theItem);
		Reduce(Board::SquareGroupType_e::Column, theItem);
		Reduce(Board::SquareGroupType_e::Block, theItem);
	}

	for (int theItem = 1; theItem <= 9; ++theItem)
	{
		RemoveStrandedSingles(Board::SquareGroupType_e::Row, theItem);
		RemoveStrandedSingles(Board::SquareGroupType_e::Column, theItem);
		RemoveStrandedSingles(Board::SquareGroupType_e::Block, theItem);
	}

	for (int theItem = 1; theItem <= 9; ++theItem)
	{
		RemoveNakedPairs(Board::SquareGroupType_e::Row, theItem);
		RemoveNakedPairs(Board::SquareGroupType_e::Column, theItem);
		RemoveNakedPairs(Board::SquareGroupType_e::Block, theItem);
	}

	for (int theItem = 1; theItem <= 9; ++theItem)
	{
		PointingPairs(Board::SquareGroupType_e::Block, theItem);
	}

	if (!(myBoard->CheckValid()))
	{
		// After the reductions I ended up invalid.
		mySolverState = SolverState::INVALID;
		DataManager<Solver>::GetInst()->RegisterCompld(this);
		return;
	}
	else if (myBoard->Solved())
	{
		// Notify the DataManager that a solution has been found

		mySolverState = SolverState::SOLVED;
		myBoardState = myBoard->GetBoardState();

		myBoard->CheckValid();

		DataManager<Solver>::GetInst()->SetScore(myBoardState);
		DataManager<Solver>::GetInst()->SolutionFound(this);
		
		return;
	}
	else
	{
		if (myBoardState == myBoard->GetBoardState())
		{
			// Our reduction techniques have done as much as they can.
			// Now we make a guess.

			if (DataManager<Solver>::GetInst()->IsGuessingEnabled())
			{
				mySolverState = SolverState::SURRENDERED;
				DataManager<Solver>::GetInst()->RegisterCompld(this);
				DataManager<Solver>::GetInst()->SetScore(myBoardState);
				MakeGuesses();
				return;
			}
			else
			{
				// This is as far as we can go without guessing, so tell the manager we are done.
				mySolverState = SolverState::SOLVED;
				DataManager<Solver>::GetInst()->SolutionFound(this);
				return;
			}
		}
		else
		{
			DataManager<Solver>::GetInst()->SetScore(myBoardState);
			std::function<void()> run_callback = std::bind(&Solver::Run, this);
			myTimerClass* tc = new myTimerClass(run_callback);
			thread* t = new thread(&myTimerClass::timer, tc, 100);
			t->detach();
		}
	}
}

void Solver::Reduce(Board::SquareGroupType_e theItemType, int theItem)
{
	myBoard->Reduce(theItemType, theItem);
}

void Solver::RemoveStrandedSingles(Board::SquareGroupType_e theItemType, int theItem)
{
	myBoard->RemoveStrandedSingles(theItemType, theItem);
}

void Solver::RemoveNakedPairs(Board::SquareGroupType_e theItemType, int theItem)
{
	myBoard->RemoveNakedPairs(theItemType, theItem);
}

void Solver::PointingPairs(Board::SquareGroupType_e theItemType, int theItem)
{
	myBoard->PointingPairs(theItemType, theItem);
}

void Solver::MakeGuesses()
{
	// Here is where we make our guesses. 
	// If you think about it, making all the guesses for one square MUST
	// produce the correct answer, so lets do that.

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			if (myBoard->GetSquareCount(i, j) > 1)
			{
				for (int k = 1; k <= 9; ++k)
				{
					if (myBoard->Contains(i,j,k))
					{
						Board* B = new Board(*(myBoard));

						B->SetSquareValue(i, j, k);
						Solver* S = new Solver();
						S->SetBoard(B);

						DataManager<Solver>::GetInst()->addElement(S);
					}
				}

				// One of these guys must be correct, so get outta here and let the solving continue.
				return;
			}
		}
	}
}
