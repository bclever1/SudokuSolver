#pragma once

#include "Board.h"
#include <memory>

class SolverPair;

class Solver
{
	public:

		Solver() {}
		~Solver() {}

		void Run();
		
		void Reduce(Board::SquareGroupType_e theItemType, int theItem);
		void RemoveStrandedSingles(Board::SquareGroupType_e theItemType, int theItem);
		void RemoveNakedPairs(Board::SquareGroupType_e theItemType, int theItem);
		void PointingPairs(Board::SquareGroupType_e theItemType, int theItem);

		void SetParent(std::shared_ptr<SolverPair> theParent)
		{
			myParent = theParent;
		}

private:

	std::shared_ptr<SolverPair> myParent;
};
