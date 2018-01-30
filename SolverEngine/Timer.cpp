#include "stdafx.h"

#include "Timer.h"
#include "TimerFactory.h"

void Timer::Run()
{
	//uint theNewTimer = myTimer * 100;

	for (uint i = 0; i < myTimer; ++i) {}

	if (!(myCallback == nullptr))
	{
		myCallback();
	}

	myWorkComplete = true;

	TimerFactory::GetInst()->TimerFired(myThread, this);
}