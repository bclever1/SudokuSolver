#pragma once

#include "Macros.h"
#include <functional>
#include <thread>
#include <string>

class Timer
{
	friend class TimerFactory;

public:

	explicit Timer(std::function<void()>theCallback, uint theTimer, std::thread::id theThread, bool theImmediate, bool recurring) : 
		myCallback(theCallback), myTimer(theTimer), myThread(theThread), isImmediate(theImmediate), isRecurring(recurring), myWorkComplete(false)
	{

	}

	Timer(const Timer& orig)
	{
		myCallback = orig.myCallback;
		myTimer = orig.myTimer;
		myThread = orig.myThread;
		myWorkComplete = orig.myWorkComplete;
		isImmediate = orig.isImmediate;
		isRecurring = orig.isRecurring;
	}

public:

	~Timer()
	{
	}

	void Start()
	{
		Run();
	}

private:

	std::function<void()>myCallback;
	uint myTimer;
	std::thread::id myThread;
	bool myWorkComplete;
	bool isImmediate;
	bool isRecurring;

	void Run();

};
