#include "stdafx.h"
#include "SudokuAPI.h"
#include "Board.h"
#include "DataManager.h"
#include "Solver.h"
#include "SolverPair.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

unsigned char* getBoardDisplay()
{
	unsigned char* values = new unsigned char[810];
	try
	{
		auto b = DataManager<SolverPair>::GetInst()->GetSolvedBoard();

		if (b != nullptr)
		{
			int byteIdx = 0;
			for (int i = 1; i <= 9; ++i)
			{
				for (int j = 1; j <= 9; ++j)
				{
					vector<int> s = b->GetSquareValues(i, j);

					for (int k = 0; k < s.size(); ++k)
					{
						values[byteIdx] = (unsigned char)(s[k]);
						++byteIdx;
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
	DataManager<SolverPair>::GetInst()->Reset();
}

extern "C" __declspec(dllexport) bool Initialize(unsigned char bytes[])
{
	std::shared_ptr<Board>b(new Board());
	std::shared_ptr<Solver>s(new Solver());
	std::shared_ptr<SolverPair>p(new SolverPair(b, s));

	s->SetParent(p);

	int byteIdx = 0;
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			b->SetValue(i, j, bytes[byteIdx]);
			++byteIdx;
		}
	}

	if (true /*Validate b*/)
	{
		DataManager<SolverPair>::GetInst()->logMessage("Starting...\n");
		DataManager<SolverPair>::GetInst()->addElement(p);
		DataManager<SolverPair>::GetInst()->logMessage("Added new board and solver pair...\n");
		return true;
	}
	else
	{
		return false;
	}
}

extern "C" __declspec(dllexport) unsigned char* GetCurrentBoard()
{
	return getBoardDisplay();
}

extern "C" __declspec(dllexport) void Solve()
{
	DataManager<SolverPair>::GetInst()->getElementAt(0)->GetSolverPtr()->Run();
}

extern "C" __declspec(dllexport) bool Solved()
{
	return DataManager<SolverPair>::GetInst()->GetSolvedYet();
}

extern "C" __declspec(dllexport) void EnableGuessing()
{
	DataManager<SolverPair>::GetInst()->EnableGuessing();
}

extern "C" __declspec(dllexport) void DisableGuessing()
{
	DataManager<SolverPair>::GetInst()->DisableGuessing();
}