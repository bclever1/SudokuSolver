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
	static std::list<T*> myData;
	static std::mutex myMutex;

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

	/* Just a pattern for future work */ 
	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	/* Start the dispatcher loop */
	void Initialize()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		while (myData.size() > 0)
		{
			myData.pop_back();
		}

		std::function<void()> run_callback = std::bind(&Dispatcher::Run, this);
		TimerFactory::GetInst()->CreateTimer(run_callback, 50, true);
	}

	/* Process the elements in my list */
	void Run()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		//TimerFactory::GetInst()->Clear();

		if (myData.size() > 0)
		{
			T* temp = *myData.begin();
			myData.pop_front();
			temp->Start();
		}

		std::function<void()> run_callback = std::bind(&Dispatcher::Run, this);
		TimerFactory::GetInst()->CreateTimer(run_callback, 50, true);
	}

	/* Add an element to my list */
	bool addElement(T* theElement)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		myData.push_back(theElement);
		return true;
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
};

template <typename T>
Dispatcher<T>* Dispatcher<T>::myInstance = nullptr;

template <typename T>
std::once_flag Dispatcher<T>::myOnceFlag;

template <typename T>
std::list<T*> Dispatcher<T>::myData;

template <typename T>
std::mutex Dispatcher<T>::myMutex;