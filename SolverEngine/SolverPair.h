#pragma once

#include <memory>
#include "Solver.h"

#if 0
class SolverPair
{
public:

	explicit SolverPair(Board* theBoard, Solver* theSolver) : myBoard(theBoard), mySolver(theSolver) {}
	explicit SolverPair(SolverPair* theSp) : myBoard(theSp->myBoard), mySolver(theSp->mySolver) {}

	~SolverPair() 
	{
		delete myBoard;
		delete mySolver;
	}

	Board* GetBoardPtr() { return myBoard; }
	Solver* GetSolverPtr() { return mySolver; }

private:
	Solver* mySolver;
	Board* myBoard;
	
};
#endif
