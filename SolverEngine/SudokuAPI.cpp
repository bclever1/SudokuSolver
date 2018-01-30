#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <bitset>

#include "Board.h"
#include "Dispatcher.h"
#include "Solver.h"
#include "SudokuManager.h"
#include "Macros.h"

using namespace std;

unsigned char* getBoardDisplay()
{
	unsigned char* values = new unsigned char[RESPONSE_SIZE];

	try
	{
		Board* B = SudokuManager<bool>::GetInst()->GetSolvedBoard();

		if (B != nullptr)
		{
			int byteIdx = 0;
			for (int i = 1; i <= 9; ++i)
			{
				for (int j = 1; j <= 9; ++j)
				{
					bitset<10>& sqr_values = B->GetSquareValues(i, j);

					for (int k = 1; k <= 9; ++k)
					{
						if (sqr_values[k] == 1)
						{
							values[byteIdx] = (unsigned char)(k);
							++byteIdx;
						}
					}
					values[byteIdx] = (unsigned char)0;
					++byteIdx;
				}
			}
		}
	}
	catch (...)
	{

	}

	return values;
}

extern "C" __declspec(dllexport) void Reset() 
{ 
	
}

extern "C" __declspec(dllexport) bool Initialize(unsigned char bytes[])
{
	SudokuManager<bool>::GetInst()->Initialize();

	Board* B = new Board();

	int byteIdx = 0;
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			B->SetValue(i, j, bytes[byteIdx]);
			++byteIdx;
		}
	}

	Solver* S = new Solver();
	S->SetBoard(B);

	SudokuManager<bool>::GetInst()->logMessage("Starting...\n");
	S->Initialize();

	SudokuManager<bool>::GetInst()->logMessage("Added new board and solver pair...\n");
	return true;
}

extern "C" __declspec(dllexport) unsigned char* GetCurrentBoard()
{
	SudokuManager<bool>::GetInst()->logMessage("Calling GetCurrentBoard!\n");
	return getBoardDisplay();
}

extern "C" __declspec(dllexport) void Solve()
{
	SudokuManager<bool>::GetInst()->logMessage("Calling Solve!\n");
}

extern "C" __declspec(dllexport) char* GetActiveSolvers()
{
	SudokuManager<bool>::GetInst()->logMessage("Calling GetActiveSolvers!\n");
	
	char* values = new char[RESPONSE_SIZE];

	for (uint i = 0; i < RESPONSE_SIZE; ++i)
	{
		values[i] = '\0';
	}

	unsigned long theActiveSolvers = SudokuManager<bool>::GetInst()->GetNumGuesses() - SudokuManager<bool>::GetInst()->GetNumInvalids() - SudokuManager<bool>::GetInst()->GetNumSurrenders();

	string myStr = std::to_string(theActiveSolvers);

	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}

extern "C" __declspec(dllexport) void EnableGuessing()
{
	SudokuManager<bool>::GetInst()->EnableGuessing();
}

extern "C" __declspec(dllexport) void DisableGuessing()
{
	SudokuManager<bool>::GetInst()->DisableGuessing();
}

extern "C" __declspec(dllexport) char* GetNumGuesses()
{
	SudokuManager<bool>::GetInst()->logMessage("Calling GetNumGuesses!\n");
	char* values = new char[RESPONSE_SIZE];

	unsigned long theGuesses = SudokuManager<bool>::GetInst()->GetNumGuesses();

	string myStr = std::to_string(theGuesses);
	
	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}

extern "C" __declspec(dllexport) char* GetNumInvalids()
{
	SudokuManager<bool>::GetInst()->logMessage("Calling GetNumInvalids!\n");

	char* values = new char[RESPONSE_SIZE];

	unsigned long theBestScore = SudokuManager<bool>::GetInst()->GetNumInvalids();

	string myStr = std::to_string(theBestScore);

	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}

extern "C" __declspec(dllexport) char* GetBestScore()
{
	char* values = new char[RESPONSE_SIZE];

	unsigned long theBestScore = SudokuManager<bool>::GetInst()->GetBestScore();

	string myStr = std::to_string(theBestScore);

	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}

extern "C" __declspec(dllexport) char* GetNumSurrenders()
{
	char* values = new char[RESPONSE_SIZE];

	unsigned long theBestScore = SudokuManager<bool>::GetInst()->GetNumSurrenders();

	string myStr = std::to_string(theBestScore);

	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}

extern "C" __declspec(dllexport) bool GetIsSolved()
{
	return SudokuManager<bool>::GetInst()->GetSolvedYet();
}

extern "C" __declspec(dllexport) bool Shutdown()
{
	return SudokuManager<bool>::GetInst()->Shutdown();
}