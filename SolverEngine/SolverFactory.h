#pragma once

#include <mutex>
#include <fstream>
#include <string>
#include <functional>
#include <thread>
#include <memory>
#include <list>

#include "Solver.h"
#include "Macros.h"

using namespace std;

class SolverFactory
{
private:

	static SolverFactory* my_instance;
	static std::once_flag my_once_flag;
	std::mutex myMutex;
	std::list<thread*> myThreads;
	std::list<thread::id> myCompletedThreads;
	bool myTerminated;

	SolverFactory()
	{
		my_instance = this;
		myTerminated = true;
	}

	void Clear() {};

public:

	void CreateSolver(Board* theBoard)
	{

	}

	static SolverFactory* GetInst()
	{
		std::call_once(SolverFactory::my_once_flag, []() {new SolverFactory(); });
		return SolverFactory::my_instance;
	}

	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	

	void Initialize()
	{
		std::lock_guard<std::mutex> guard(myMutex);
		
		Clear();
	}
};