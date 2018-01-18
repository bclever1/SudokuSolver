#pragma once

#include <memory>
#include "Solver.h"

class SolverPair
{
public:

	SolverPair(std::shared_ptr<Board> theBoard, std::shared_ptr<Solver> theSolver) : myBoard(theBoard), mySolver(theSolver) {}
	~SolverPair() 
	{
	
	}

	std::shared_ptr<Board> GetBoardPtr() { return myBoard; }
	std::shared_ptr<Solver> GetSolverPtr() { return mySolver; }

private:
	std::shared_ptr<Board> myBoard;
	std::shared_ptr<Solver> mySolver;
};