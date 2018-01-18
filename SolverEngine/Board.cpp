#include "stdafx.h"

#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

#include "Board.h"
#include "Square.h"
#include "DataManager.h"
#include "SolverPair.h"

using namespace std;

int Board::square_to_block_map[10][10] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 0, 1, 1, 1, 2, 2, 2, 3, 3, 3 },
	{ 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
	{ 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
	{ 0, 4, 4, 4, 5, 5, 5, 6, 6, 6 },
	{ 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 },
	{ 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 },
	{ 0, 7, 7, 7, 8, 8, 8, 9, 9, 9 }
};

Board::Board()
{
	std::lock_guard<std::mutex> guard(myMutex);

	for (int i = 0; i <= 9; ++i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			mySquares[i][j] = nullptr;
		}
	}

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			mySquares[i][j] = new Square(i, j);

			myRows[i].push_back(mySquares[i][j]);
			myColumns[j].push_back(mySquares[i][j]);

			if (1 <= i && i <= 3)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[1].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[2].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[3].push_back(mySquares[i][j]);
				}
			}
			if (4 <= i && i <= 6)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[4].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[5].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[6].push_back(mySquares[i][j]);
				}
			}
			if (7 <= i && i <= 9)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[7].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[8].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[9].push_back(mySquares[i][j]);
				}
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i <= 9; ++i)
	{
		myRows[i].clear();
		delete [] myRows;

		myColumns[i].clear();
		delete [] myColumns;

		myBlocks[i].clear();
		delete [] myBlocks;
	}

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			Square* temp = mySquares[i][j];
			mySquares[i][j] = 0;
			delete temp;
		}
	}
}

void Board::SetValue(int row, int col, int theVal)
{
	std::lock_guard<std::mutex> guard(myMutex);
	mySquares[row][col]->setValue(theVal);
}

int Board::GetValue(int i, int j)
{
	std::lock_guard<std::mutex> guard(myMutex);
	return 0;
}

struct mySquareFunctor
{
	bool operator()(Square* s)
	{
		if (s->getCount() > 1)
		{
			return false;
		}

		return true;
	}
};

bool Board::Solved()
{
	std::lock_guard<std::mutex> guard(myMutex);
	mySquareFunctor f;
	bool theResult = true;

	for (int i = 1; i <= 9; ++i)
	{
		for (std::vector<Square*>::iterator itr = myBlocks[i].begin();
			itr != myBlocks[i].end();
			++itr)
		{
			if (!f((*itr)))
			{
				return false;
			}
		}
	}
	return true;

}

void Board::Reduce(Board::SquareGroupType_e theGrpType, int theItem)
{
	std::lock_guard<std::mutex> guard(myMutex);
	DataManager<SolverPair>::GetInst()->logMessage("Here 1 in Board::Reduce...\n");

	vector<Square*>* grpToReduce = nullptr;

	if (theGrpType == Board::SquareGroupType_e::Row)
	{
		grpToReduce = &myRows[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Column)
	{
		grpToReduce = &myColumns[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Block)
	{
		grpToReduce = &myBlocks[theItem];
	}

	if (grpToReduce == nullptr) return;

	for (int reducer = 1; reducer <= 9; ++reducer)
	{
		// See if we can reduce this number
		// If the square contains this number as a singleton we can remove it from the other squares

		int theCount = 0;

		for (std::vector<Square*>::iterator itr = grpToReduce->begin();
			itr != grpToReduce->end();
			++itr)
		{
			if ((*itr)->getCount() == 1 && (*itr)->contains(reducer))
			{
				++theCount;
			}
		}

		if (theCount == 1)
		{
			// Remove the reducer from all the squares except the singleton
			for (std::vector<Square*>::iterator itr1 = grpToReduce->begin();
				itr1 != grpToReduce->end();
				++itr1)
			{
				if ((*itr1) == nullptr || (*itr1) == 0)
				{
					return;
				}

				if ((*itr1)->getCount() > 1)
				{
					(*itr1)->remove(reducer);
				}
			}
		}
	}

	DataManager<SolverPair>::GetInst()->logMessage("Leaving Board::Reduce...\n");
}


void Board::RemoveStrandedSingles(Board::SquareGroupType_e theGrpType, int theItem)
{
	std::lock_guard<std::mutex> guard(myMutex);
	DataManager<SolverPair>::GetInst()->logMessage("Here 1 in Board::RemoveStrandedSingles...\n");

	vector<Square*>* v = nullptr;

	if (theGrpType == Board::SquareGroupType_e::Row)
	{
		v = &myRows[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Column)
	{
		v = &myColumns[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Block)
	{
		v = &myBlocks[theItem];
	}

	for (int reducer = 1; reducer <= 9; ++reducer)
	{
		bool isSingleton = false;

		// Check the vector v for the reducer value.
		// If reducer only occurs once in the set of squares we can remove all other values
		//vector<Square*>* theContainer = new vector<Square*>();

		for (std::vector<Square*>::iterator itr = v->begin();
			itr != v->end();
			++itr)

		{
			if ((*itr)->getCount() == 1 && (*itr)->contains(reducer))
			{
				// This value is a singleton, we don't need to go any further
				isSingleton = true;
				break;
			}
		}

		if (isSingleton) continue;

		int theCount = 0;
		Square* theGoodSquare = nullptr;

		for (std::vector<Square*>::iterator itr = v->begin();
			itr != v->end();
			++itr)

		{
			if ((*itr)->getCount() > 1 && (*itr)->contains(reducer))
			{
				theGoodSquare = *itr;
				++theCount;
			}
		}

		if (theCount == 1 && theGoodSquare != nullptr)
		{
			// This is the only square that has the value.
			theGoodSquare->removeAllExcept(reducer);
		}
	}

	DataManager<SolverPair>::GetInst()->logMessage("Leaving Board::RemoveStrandedSingles...\n");
}


void Board::RemoveNakedPairs(Board::SquareGroupType_e theGrpType, int theItem)
{
	std::lock_guard<std::mutex> guard(myMutex);

	DataManager<SolverPair>::GetInst()->logMessage("Here 1 in Board::RemoveNakedPairs...\n");

	vector<Square*> v;

	if (theGrpType == Board::SquareGroupType_e::Row)
	{
		v = myRows[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Column)
	{
		v = myColumns[theItem];
	}
	else if (theGrpType == Board::SquareGroupType_e::Block)
	{
		v = myBlocks[theItem];
	}

	for (int pair1 = 1; pair1 <= 8; ++pair1)
	{
		for (int pair2 = pair1 + 1; pair2 <= 9; ++pair2)
		{
			vector<int> thePair{ pair1, pair2 };

			// Scan the squares of v to see if they equal this pair... if we find two we've got a naked pair

			int pairCount = 0;
			vector<Square*> thePairSet;

			for (std::vector<Square*>::iterator itr = v.begin();
				itr != v.end();
				++itr)
			{
				if ((*itr)->compareValues(thePair))
				{
					thePairSet.push_back((*itr));
				}
			}

			if (thePairSet.size() == 2)
			{
				// Found a naked pair! We can remove pair1 and pair2 from all other squares

				for (std::vector<Square*>::iterator itr = v.begin();
					itr != v.end();
					++itr)
				{
					if ((*itr) != thePairSet[0] && (*itr != thePairSet[1]))
					{
						if ((*itr)->contains(pair1))
						{
							(*itr)->remove(pair1);
						}
						if ((*itr)->contains(pair2))
						{
							(*itr)->remove(pair2);
						}
					}
				}
			}
		}
	}

	DataManager<SolverPair>::GetInst()->logMessage("Leaving Board::RemoveNakedPairs...\n");
}


void Board::PointingPairs(Board::SquareGroupType_e theGrpType, int theItem)
{
	std::lock_guard<std::mutex> guard(myMutex);

	DataManager<SolverPair>::GetInst()->logMessage("Here 1 in Board::PointingPairs...\n");

	for (int reducer = 1; reducer <= 9; ++reducer)
	{
		// See if we can reduce this number
	
		// Go through the blocks to see if the reducer must be in a particular row or column.
		// If it must be, then remove the reducer from the associated blocks' rows or columns.

		vector<Square*> theGoodSquares;

		for (std::vector<Square*>::iterator sqr = myBlocks[theItem].begin();
			sqr != myBlocks[theItem].end();
			++sqr)
		{
			if ((*sqr)->contains(reducer))
			{
				theGoodSquares.push_back((*sqr));
			}
		}
		if (theGoodSquares.size() >= 2)
		{
			vector<int> theRowNums;
			vector<int> theColNums;

			for (std::vector<Square*>::iterator good_sqr = theGoodSquares.begin();
				good_sqr != theGoodSquares.end();
				++good_sqr)
			{
				theRowNums.push_back((*good_sqr)->GetRowNum());
				theColNums.push_back((*good_sqr)->GetColNum());
			}

			std::vector<int>::iterator rowItr = std::unique(theRowNums.begin(), theRowNums.end());
			theRowNums.resize(std::distance(theRowNums.begin(), rowItr));

			std::vector<int>::iterator colItr = std::unique(theColNums.begin(), theColNums.end());
			theColNums.resize(std::distance(theColNums.begin(), colItr));

			if (theRowNums.size() == 1)
			{
				// This means reducer only exists in this row in this block.
				// Therefore we can remove reducer from the intersection of this row
				// and the other blocks.

				int theRow = theRowNums[0];
				int the_complement_1;
				int the_complement_2;

				Board::GetBlockRowComplement(theItem, the_complement_1, the_complement_2);

				for (std::vector<Square*>::iterator itx = myRows[theRow].begin();
					itx != myRows[theRow].end();
					++itx)
				{
					if (Board::GetBlock((*itx)->GetRowNum(), (*itx)->GetColNum()) == the_complement_1 ||
						Board::GetBlock((*itx)->GetRowNum(), (*itx)->GetColNum()) == the_complement_2)
					{
						if ((*itx)->contains(reducer))
						{
							(*itx)->remove(reducer);
						}
					}
				}
			}

			if (theColNums.size() == 1)
			{
				// This means reducer only exists in this column in this block.
				// Therefore we can remove reducer from the intersection of this row
				// and the other blocks.

				int theCol = theColNums[0];
				int the_complement_1;
				int the_complement_2;

				Board::GetBlockColumnComplement(theItem, the_complement_1, the_complement_2);

				for (std::vector<Square*>::iterator itx = myColumns[theCol].begin();
					itx != myColumns[theCol].end();
					++itx)
				{
					if (Board::GetBlock((*itx)->GetRowNum(), (*itx)->GetColNum()) == the_complement_1 ||
						Board::GetBlock((*itx)->GetRowNum(), (*itx)->GetColNum()) == the_complement_2)
					{
						if ((*itx)->contains(reducer))
						{
							(*itx)->remove(reducer);
						}
					}
				}
			}
		}
	}

	DataManager<SolverPair>::GetInst()->logMessage("Leaving Board::PointingPairs...\n");
}

int Board::GetBoardState()
{
	std::lock_guard<std::mutex> guard(myMutex);

	int result = 0;

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			result += mySquares[i][j]->getValue();
		}
	}

	return result;
}

Board::Board(Board* b)
{
	std::lock_guard<std::mutex> guard(myMutex);

	for (int i = 0; i <= 9; ++i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			mySquares[i][j] = nullptr;
		}
	}

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			mySquares[i][j] = new Square(i, j);

			myRows[i].push_back(mySquares[i][j]);
			myColumns[j].push_back(mySquares[i][j]);

			if (1 <= i && i <= 3)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[1].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[2].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[3].push_back(mySquares[i][j]);
				}
			}
			if (4 <= i && i <= 6)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[4].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[5].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[6].push_back(mySquares[i][j]);
				}
			}
			if (7 <= i && i <= 9)
			{
				if (1 <= j && j <= 3)
				{
					myBlocks[7].push_back(mySquares[i][j]);
				}
				if (4 <= j && j <= 6)
				{
					myBlocks[8].push_back(mySquares[i][j]);
				}
				if (7 <= j && j <= 9)
				{
					myBlocks[9].push_back(mySquares[i][j]);
				}
			}
		}
	}

	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			mySquares[i][j]->copyValues(b->mySquares[i][j]->getValues());
		}
	}
}

struct validityChecker
{
	bool myResult;
	void operator()(vector<Square*>&v)
	{
		int theCounts[10]{ 0,0,0,0,0,0,0,0,0,0 };
	}
};

bool Board::CheckValid()
{
	bool theResult = true;

	// If any row, column or block contains two or ore singletons then invalid
	{
		for (int r = 1; r <= 9; ++r)
		{
			int theCounts[10]{ 0,0,0,0,0,0,0,0,0,0 };

			for (std::vector<Square*>::iterator sqr = myRows[r].begin();
				sqr != myRows[r].end();
				++sqr)
			{
				if ((*sqr)->getCount() == 1)
				{
					++theCounts[(*sqr)->getPos(0)];
				}
			}

			for (int i = 0; i < 10; ++i)
			{
				if (theCounts[i] > 1)
				{
					return false;
				}
			}
		}
	}

	{
		for (int c = 1; c <= 9; ++c)
		{
			int theCounts[10]{ 0,0,0,0,0,0,0,0,0,0 };

			for (std::vector<Square*>::iterator sqr = myColumns[c].begin();
				sqr != myColumns[c].end();
				++sqr)
			{
				if ((*sqr)->getCount() == 1)
				{
					++theCounts[(*sqr)->getPos(0)];
				}
			}

			for (int i = 0; i < 10; ++i)
			{
				if (theCounts[i] > 1)
				{
					return false;
				}
			}
		}
	}

	{

		for (int b = 1; b <= 9; ++b)
		{
			int theCounts[10]{ 0,0,0,0,0,0,0,0,0,0 };

			for (std::vector<Square*>::iterator sqr = myBlocks[b].begin();
				sqr != myBlocks[b].end();
				++sqr)
			{
				if ((*sqr)->getCount() == 1)
				{
					++theCounts[(*sqr)->getPos(0)];
				}
			}

			for (int i = 0; i < 10; ++i)
			{
				if (theCounts[i] > 1)
				{
					return false;
				}
			}
		}
	}
	return true;
}

vector<int> Board::GetSquareValues(int row, int col)
{
	return mySquares[row][col]->getValues();
}


void Board::MakeGuesses()
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (DataManager<SolverPair>::GetInst()->GetSolvedYet() == false)
	{

		for (int i = 1; i <= 9; ++i)
		{
			for (int j = 1; j <= 9; ++j)
			{
				if (mySquares[i][j]->getCount() == 2)
				{
					for (int pos = 0; pos < 2; ++pos)
					{
						std::shared_ptr<Board>b(new Board(this));

						b.get()->RemoveValueFromSquare(i, j, mySquares[i][j]->getPos(pos));

						std::shared_ptr<Solver>s(new Solver());
						std::shared_ptr<SolverPair>p(new SolverPair(b, s));

						s->SetParent(p);

						try
						{
							DataManager<SolverPair>::GetInst()->addElement(p);
							s->Run();
						}
						catch (...)
						{
						}
					}
				}
			}
		}
	}
}

void Board::RemoveValueAtPosFromSquare(int row, int col, int thePos)
{
	std::lock_guard<std::mutex> guard(myMutex);
	mySquares[row][col]->remove(thePos);
}

void Board::RemoveValueFromSquare(int row, int col, int thePos)
{
	std::lock_guard<std::mutex> guard(myMutex);
	mySquares[row][col]->remove(thePos);
}

void Board::GetBlockRowComplement(int theBlock, int& compl_1, int& compl_2)
{
	switch (theBlock)
	{
	case 1: compl_1 = 2; compl_2 = 3; return;
	case 2: compl_1 = 1; compl_2 = 3; return;
	case 3: compl_1 = 1; compl_2 = 2; return;
	case 4: compl_1 = 5; compl_2 = 6; return;
	case 5: compl_1 = 4; compl_2 = 6; return;
	case 6: compl_1 = 4; compl_2 = 5; return;
	case 7: compl_1 = 8; compl_2 = 9; return;
	case 8: compl_1 = 7; compl_2 = 9; return;
	case 9: compl_1 = 7; compl_2 = 8; return;
	default: compl_1 = -1; compl_2 = -1; return;
	};
}

void Board::GetBlockColumnComplement(int theBlock, int& compl_1, int& compl_2)
{
	switch (theBlock)
	{
	case 1: compl_1 = 4; compl_2 = 7; return;
	case 2: compl_1 = 5; compl_2 = 8; return;
	case 3: compl_1 = 6; compl_2 = 9; return;
	case 4: compl_1 = 1; compl_2 = 7; return;
	case 5: compl_1 = 2; compl_2 = 8; return;
	case 6: compl_1 = 3; compl_2 = 9; return;
	case 7: compl_1 = 1; compl_2 = 4; return;
	case 8: compl_1 = 2; compl_2 = 5; return;
	case 9: compl_1 = 3; compl_2 = 6; return;
	default: compl_1 = -1; compl_2 = -1; return;
	};
}