#pragma once

#include "Board.h"
#include <memory>

class Solver
{
	public:

		enum SolverState {
			ACTIVE,
			READY,
			INVALID,
			RUNNING,
            SURRENDERED,
			SOLVED
		};

		explicit Solver() : myBoard(nullptr), mySolverState(SolverState::READY) 
		{
		}
		explicit Solver(const Solver& s) : myBoard(s.myBoard), mySolverState(s.mySolverState) 
		{
		}
		
		~Solver() {}

		void Run();
		
		void Reduce(Board::SquareGroupType_e theItemType, int theItem);
		void RemoveStrandedSingles(Board::SquareGroupType_e theItemType, int theItem);
		void RemoveNakedPairs(Board::SquareGroupType_e theItemType, int theItem);
		void PointingPairs(Board::SquareGroupType_e theItemType, int theItem);

		void ClearBoard()
		{
			myBoard = nullptr;
		}

		void SetBoard(Board* theBoard) { myBoard = theBoard; }
		Board* GetBoard() { return myBoard; }

		Solver::SolverState GetState() { return mySolverState; }

private:

	void MakeGuesses();

	SolverState mySolverState;
	Board* myBoard;
	std::mutex myMutex;
	
};
