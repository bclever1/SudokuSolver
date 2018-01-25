#include "stdafx.h"
#include "SudokuAPI.h"
#include "Board.h"
#include "DataManager.h"
#include "Solver.h"
#include "Solver.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <bitset>

using namespace std;

unsigned char* getBoardDisplay()
{
	unsigned char* values = new unsigned char[810];

	try
	{
		std::unique_ptr<Solver>* s = DataManager<Solver>::GetInst()->GetSolvedBoard();

		if (s != nullptr)
		{
			int byteIdx = 0;
			for (int i = 1; i <= 9; ++i)
			{
				for (int j = 1; j <= 9; ++j)
				{
					bitset<10>& sqr_values = s->get()->GetBoard()->GetSquareValues(i, j);
			
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
	DataManager<Solver>::GetInst()->Reset();
}

extern "C" __declspec(dllexport) bool Initialize(unsigned char bytes[])
{
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

	DataManager<Solver>::GetInst()->logMessage("Starting...\n");
	DataManager<Solver>::GetInst()->Initialize();
	DataManager<Solver>::GetInst()->addElement(S);
	DataManager<Solver>::GetInst()->logMessage("Added new board and solver pair...\n");
	return true;
}

extern "C" __declspec(dllexport) unsigned char* GetCurrentBoard()
{
	DataManager<Solver>::GetInst()->logMessage("Calling GetCurrentBoard!\n");
	return getBoardDisplay();
}

extern "C" __declspec(dllexport) void Solve()
{
	DataManager<Solver>::GetInst()->logMessage("Calling Solve!\n");
	DataManager<Solver>::GetInst()->Execute();
}

extern "C" __declspec(dllexport) bool IsSolved()
{
	DataManager<Solver>::GetInst()->logMessage("Calling Solved!\n");
	return DataManager<Solver>::GetInst()->GetSolvedYet();
}

extern "C" __declspec(dllexport) void EnableGuessing()
{
	DataManager<Solver>::GetInst()->EnableGuessing();
}

extern "C" __declspec(dllexport) void DisableGuessing()
{
	DataManager<Solver>::GetInst()->DisableGuessing();
}

extern "C" __declspec(dllexport) char* GetNumGuesses()
{
	char* values = new char[810];

	unsigned long theGuesses = DataManager<Solver>::GetInst()->GetNumGuesses();

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
	char* values = new char[810];

	unsigned long theBestScore = DataManager<Solver>::GetInst()->GetNumInvalids();

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
	char* values = new char[810];

	unsigned long theBestScore = DataManager<Solver>::GetInst()->GetBestScore();

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
	char* values = new char[810];

	unsigned long theBestScore = DataManager<Solver>::GetInst()->GetNumSurrenders();

	string myStr = std::to_string(theBestScore);

	for (uint i = 0; i < myStr.length(); ++i)
	{
		values[i] = myStr.c_str()[i];
	}
	values[myStr.length()] = '\0';

	return values;
}