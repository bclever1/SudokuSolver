#pragma once

#include "Board.h"
#include <memory>

class Solver
{
	public:

		enum SolverState {
			ACTIVE,
			READY,
			INITIALIZING,
			INVALID,
			RUNNING,
            SURRENDERED,
			SOLVED
		};

		Solver() : myBoard(nullptr), mySolverState(SolverState::INITIALIZING)
		{
		}
		Solver(const Solver& s) : myBoard(s.myBoard), mySolverState(s.mySolverState) 
		{
		}
		Solver(Solver* s) : myBoard(s->myBoard), mySolverState(s->mySolverState)
		{
		}

		//Solver(const std::shared_ptr<Solver>& s)
	//	{
	//	}
		
		~Solver()
		{
			delete myBoard;
		}

		void Initialize();

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

		void SetState(Solver::SolverState theState) { mySolverState = theState; }
		Solver::SolverState GetState() { return mySolverState; }

private:

	void MakeGuesses();

	SolverState mySolverState;
	Board* myBoard;
	std::mutex myMutex;
	
};
