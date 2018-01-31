#include "stdafx.h"

#include "Timer.h"
#include "TimerFactory.h"

#include <thread>
#include <chrono>

void Timer::Run()
{
	std::chrono::nanoseconds ms(myTimer);

	std::this_thread::sleep_for(ms);

	if (!(myCallback == nullptr))
	{
		myCallback();
	}

	myWorkComplete = true;

	TimerFactory::GetInst()->TimerFired(myThread, this);
}