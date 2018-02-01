#pragma once

#include "Board.h"
#include <memory>


class Solver
{
	public:

		static int DEBUG_SOLVER_COUNTER;

		enum SolverState {
			ACTIVE,
			READY,
			INITIALIZING,
			INVALID,
			RUNNING,
            SURRENDERED,
			SOLVED
		};

		Solver(unsigned char bytes[])
		{
			myBoard = std::make_unique<Board>(new Board());

			int byteIdx = 0;
			for (int i = 1; i <= 9; ++i)
			{
				for (int j = 1; j <= 9; ++j)
				{
					myBoard->SetValue(i, j, bytes[byteIdx]);
					++byteIdx;
				}
			}

			myConstructorId = 1;
			mySolverId = DEBUG_SOLVER_COUNTER++;
			myRunCounter = 0;

		}

		Solver(Board& theBoard) : mySolverState(SolverState::INITIALIZING)
		{
			myBoard = std::make_unique<Board>(theBoard);
			myConstructorId = 2;
			mySolverId = DEBUG_SOLVER_COUNTER++;
			myRunCounter = 0;
		}

		Solver(const Solver& s) : mySolverState(s.mySolverState)
		{
			myBoard = std::make_unique<Board>((*s.myBoard));
			myConstructorId = 3;
			mySolverId = DEBUG_SOLVER_COUNTER++;
			myRunCounter = 0;
		}
		
		~Solver()
		{
		//	delete myBoard;
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

//		void SetBoard(Board* theBoard) { myBoard = theBoard; }
		std::unique_ptr<Board>* GetBoard() { return &myBoard; }

		void SetState(Solver::SolverState theState) { mySolverState = theState; }
		Solver::SolverState GetState() { return mySolverState; }

private:

	void MakeGuesses();

	SolverState mySolverState;
	std::unique_ptr<Board> myBoard;
	std::mutex myMutex;
	int myConstructorId;
	int mySolverId;
	int myRunCounter;
	
};