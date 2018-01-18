#pragma once
#include <vector>
#include <mutex>

using namespace std;

class displayGrid;
class Square;

class Board
{
public:

	typedef enum {Row, Column, Block} SquareGroupType_e;

	Board();
	~Board();

	Board(Board* b);

	/* Return the state of square[i,j]... a summation of all its values */
	int GetValue(int i, int j);

	/* Set a particular value in square[i,j]. This will remove all other values.*/
	void SetValue(int i, int j, int theVal);

	/* Do simple row, column and block reduction based on squares containing a known value.*/
	void Reduce(Board::SquareGroupType_e theType, int theIdx);

	/* Search for entries that must be known but hidden in a square with multiple values. */
	void RemoveStrandedSingles(Board::SquareGroupType_e theGrpType, int theItem);

	/* Eliminate entries in rows, columns and blocks because a naked pair is known. */
	void RemoveNakedPairs(Board::SquareGroupType_e theGrpType, int theItem);

	/* Eliminate entries in rows and columns because a block has a certain configuration*/
	void PointingPairs(Board::SquareGroupType_e theGrpType, int theItem);

	/* Returns an int that indicates the current state of the board. */
	int GetBoardState();

	/* Is the current state valid?*/
	bool CheckValid();

	/* Is the current state a solution?*/
	bool Solved();

	/* Get the contents of square[row,col]*/
	vector<int> GetSquareValues(int row, int col);

	/* Start the guessing process for this board. */
	void MakeGuesses();

	/* Remove the value at position thePos from square[row,col]. */
	void RemoveValueAtPosFromSquare(int row, int col, int thePos);

	/* Remove theVal from square[row,col]. */
	void RemoveValueFromSquare(int row, int col, int theVal);

	/* Given a block, what are the other blocks row-wise? */
	static void GetBlockRowComplement(int theBlock, int& compl_1, int& compl_2);

	/* Given a block, what are the other blocks column-wise? */
	static void GetBlockColumnComplement(int theBlock, int& compl_1, int& compl_2);

	/* Get the block number of square[theRow, theCol]. */
	static int GetBlock(int theRow, int theCol)
	{
		return square_to_block_map[theRow][theCol];
	}

private:

	Square* mySquares[10][10];

	vector<Square*> myBlocks[10];
	vector<Square*> myRows[10];
	vector<Square*> myColumns[10];

	std::mutex myMutex;

	static int square_to_block_map[10][10];

};
