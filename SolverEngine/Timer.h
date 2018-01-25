#pragma once

#include "DataManager.h"

//template <typename W>
class myTimerClass
{
public:

	myTimerClass(std::function<void()>theCallback) : myCallback(theCallback)
	{
		
	}

	~myTimerClass() {}

	void timer(int theTime)
	{
		for (int i = 0; i < theTime; ++i) {}

		myCallback();
	}

	std::function<void()>myCallback;
};
