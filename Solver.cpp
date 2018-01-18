#include "stdafx.h"
#include "Solver.h"
#include "SolverPair.h"
#include "DataManager.h"

#include <thread>

void Solver::Run()
{
	vector<thread*>myThreads;

	int myBoardState;

	if (!(myParent->GetBoardPtr().get()->CheckValid())) return;

	while (true)
	{
		if (DataManager<SolverPair>::GetInst()->GetSolvedYet())
		{
			break;
		}

		myBoardState = myParent->GetBoardPtr().get()->GetBoardState();
		myThreads.clear();

		// Do the obvious reductions of the rows, columns and blocks
		DataManager<SolverPair>::GetInst()->logMessage("Here 1 in Solver::Run...\n");
		for (int theItem = 1; theItem <= 9; ++theItem)
		{
			myThreads.push_back(new thread(&Solver::Reduce, this, Board::SquareGroupType_e::Row, theItem));
			myThreads.push_back(new thread(&Solver::Reduce, this, Board::SquareGroupType_e::Column, theItem));
			myThreads.push_back(new thread(&Solver::Reduce, this, Board::SquareGroupType_e::Block, theItem));
		}
		DataManager<SolverPair>::GetInst()->logMessage("Here 2 in Solver::Run...\n");

		for (int theItem = 1; theItem <= 9; ++theItem)
		{
			myThreads.push_back(new thread(&Solver::RemoveStrandedSingles, this, Board::SquareGroupType_e::Row, theItem));
			myThreads.push_back(new thread(&Solver::RemoveStrandedSingles, this, Board::SquareGroupType_e::Column, theItem));
			myThreads.push_back(new thread(&Solver::RemoveStrandedSingles, this, Board::SquareGroupType_e::Block, theItem));
		}

		DataManager<SolverPair>::GetInst()->logMessage("Here 3 in Solver::Run...\n");
		for (int theItem = 1; theItem <= 9; ++theItem)
		{
			myThreads.push_back(new thread(&Solver::RemoveNakedPairs, this, Board::SquareGroupType_e::Row, theItem));
			myThreads.push_back(new thread(&Solver::RemoveNakedPairs, this, Board::SquareGroupType_e::Column, theItem));
			myThreads.push_back(new thread(&Solver::RemoveNakedPairs, this, Board::SquareGroupType_e::Block, theItem));
		}

		for (int theItem = 1; theItem <= 9; ++theItem)
		{
			myThreads.push_back(new thread(&Solver::PointingPairs, this, Board::SquareGroupType_e::Block, theItem));
		}

		DataManager<SolverPair>::GetInst()->logMessage("Here 4 in Solver::Run...\n");
		for (int t = 0; t < myThreads.size(); ++t)
		{
			myThreads[t]->join();
		}

		if (myParent->GetBoardPtr().get()->Solved())
		{
			// Notify the DataManager that a solution has been found
			DataManager<SolverPair>::GetInst()->SolutionFound(myParent);
			return;
		}

		else if (!(myParent->GetBoardPtr().get()->CheckValid()))
		{
			return;
		}
		else
		{
			if (myBoardState == myParent->GetBoardPtr().get()->GetBoardState())
			{
				// Our reduction techniques have done as much as they can.
				// Now we make a guess.

				if (DataManager<SolverPair>::GetInst()->IsGuessingEnabled())
				{
					myParent->GetBoardPtr().get()->MakeGuesses();
				}
				else
				{
					// This is as far as we can go without guessing, so tell the manager we are done.
					DataManager<SolverPair>::GetInst()->SolutionFound(myParent);
					return;

				}

				return;
			}
		}
	}
}

void Solver::Reduce(Board::SquareGroupType_e theItemType, int theItem)
{
	myParent.get()->GetBoardPtr()->Reduce(theItemType, theItem);
}

void Solver::RemoveStrandedSingles(Board::SquareGroupType_e theItemType, int theItem)
{
	myParent.get()->GetBoardPtr()->RemoveStrandedSingles(theItemType, theItem);
}

void Solver::RemoveNakedPairs(Board::SquareGroupType_e theItemType, int theItem)
{
    myParent.get()->GetBoardPtr()->RemoveNakedPairs(theItemType, theItem);
}

void Solver::PointingPairs(Board::SquareGroupType_e theItemType, int theItem)
{
	myParent.get()->GetBoardPtr()->PointingPairs(theItemType, theItem);
}