#pragma once


#include <mutex>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <utility>

#include "Board.h"
#include "Timer.h"
#include "Solver.h"
#include "Macros.h"
#include "TimerFactory.h"

template <typename T>
class Dispatcher
{
private:

	static Dispatcher<T>* myInstance;
	static std::once_flag myOnceFlag;
	std::list<T*> myData;
	std::mutex myMutex;

	Dispatcher()
	{
		myInstance = this;
	}

public:

	static Dispatcher* GetInst()
	{
		std::call_once(Dispatcher::myOnceFlag, []() {new Dispatcher(); });
		return Dispatcher::myInstance;
	}

	virtual void Initialize()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		while (myData.size() > 0)
		{
			T* temp = (*myData.begin());
			myData.pop_front();
			delete temp;
		}

		std::function<void()> run_callback = std::bind(&Dispatcher::Run, this);
		TimerFactory::GetInst()->CreateTimer(run_callback, MY_DISPATCHER_CLOCK_RATE, true, true);
	}

	/* Add an element to my list */
	bool addElement(T* theElement)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		myData.push_back(theElement);
		return true;
	}

	/* Just a pattern for future work */
	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	/* Clear my list */
	void Reset()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		while (myData.size() > 0)
		{
			myData.pop_back();
		}
	}


	virtual void Run()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		if (myData.size() > 0)
		{
			T* temp = (*myData.begin());
			myData.pop_front();
			temp->Start();
			delete temp;
		}
	}
};

template <typename T>
Dispatcher<T>* Dispatcher<T>::myInstance = nullptr;

template <typename T>
std::once_flag Dispatcher<T>::myOnceFlag;