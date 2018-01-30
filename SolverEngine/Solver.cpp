#include "stdafx.h"


#include <thread>
#include <time.h>

#include "Solver.h"
#include "Board.h"
#include "SudokuManager.h"
#include "Dispatcher.h"
#include "TimerFactory.h"

void Solver::Initialize()
{
	mySolverState = SolverState::READY;
	std::function<void()> run_callback = std::bind(&Solver::Run, this);
	TimerFactory::GetInst()->CreateTimer(run_callback, 100000, false, false);
}

void Solver::Run()
{
	mySolverState = SolverState::RUNNING;

	if (!(myBoard->CheckValid()))
	{
		// I was created invalid. Bummer.
		mySolverState = SolverState::INVALID;
		SudokuManager<bool>::GetInst()->RegisterCompld(mySolverState);
		return;
	}

	if (SudokuManager<bool>::GetInst()->GetSolvedYet())
	{
		mySolverState = SolverState::SURRENDERED;
		SudokuManager<bool>::GetInst()->RegisterCompld(mySolverState);
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
		SudokuManager<bool>::GetInst()->RegisterCompld(mySolverState);
		return;
	}
	else if (myBoard->Solved())
	{
		// Notify the DataManager that a solution has been found

		mySolverState = SolverState::SOLVED;
		myBoardState = myBoard->GetBoardState();

		myBoard->CheckValid();

		SudokuManager<bool>::GetInst()->SetScore(myBoardState);
		SudokuManager<bool>::GetInst()->SolutionFound(myBoard);
		
		return;
	}
	else
	{
		if (myBoardState == myBoard->GetBoardState())
		{
			// Our reduction techniques have done as much as they can.
			// Now we make a guess.

			if (SudokuManager<bool>::GetInst()->IsGuessingEnabled())
			{
				mySolverState = SolverState::SURRENDERED;
				SudokuManager<bool>::GetInst()->RegisterCompld(mySolverState);
				SudokuManager<bool>::GetInst()->SetScore(myBoardState);
				MakeGuesses();
				return;
			}
			else
			{
				// This is as far as we can go without guessing, so tell the manager we are done.
				mySolverState = SolverState::SOLVED;
				SudokuManager<bool>::GetInst()->SolutionFound(myBoard);
				return;
			}
		}
		else
		{
			SudokuManager<bool>::GetInst()->SetScore(myBoardState);

			std::function<void()> run_callback = std::bind(&Solver::Run, this);
			TimerFactory::GetInst()->CreateTimer(run_callback, 100000, false, false);
			mySolverState = SolverState::READY;

			return;
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
	// produce the correct answer eventually, so lets do that.

	bool finished = false;
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
						SudokuManager<bool>::GetInst()->RegisterCompld(SolverState::INITIALIZING);
						Board* B = new Board(*(myBoard));

						B->SetSquareValue(i, j, k);
						Solver* S = new Solver();
						S->SetBoard(B);
						S->Initialize();
					}
				}

				// One of these guys must be correct, so get outta here and let the solving continue.
				finished = true;
				break;
			}
		}

		if (finished == true)
		{
			break;
		}
	}

	return;
}
