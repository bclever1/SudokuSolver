#pragma once

#include "Macros.h"
#include <functional>
//#include "TimerFactory.h"
#include <thread>
#include <string>

class Timer
{
	//friend class TimerFactory;

public:

	explicit Timer(std::function<void()>theCallback, uint theTimer, std::thread::id theThread) : myCallback(theCallback), myTimer(theTimer), myThread(theThread), myWorkComplete(false)
	{

	}

	Timer(const Timer& orig)
	{
		myCallback = orig.myCallback;
		myTimer = orig.myTimer;
		myThread = orig.myThread;
		myWorkComplete = orig.myWorkComplete;
	}

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

	void Run();

};
