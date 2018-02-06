#include "stdafx.h"
#include "TimerFactory.h"
#include "Timer.h"
#include "Dispatcher.h"

TimerFactory* TimerFactory::my_instance = nullptr;
std::once_flag TimerFactory::my_once_flag;

void TimerFactory::CreateTimerOnThread(std::function<void()>theCallback, uint theTimer, bool theImmediate, bool recurring)
{
	if (theImmediate)
	{
		Timer p(theCallback, theTimer, std::this_thread::get_id(), theImmediate, recurring);
		p.Start();
	}
	else
	{
		std::unique_ptr<Timer> p = std::make_unique<Timer>(Timer(theCallback, theTimer, std::this_thread::get_id(), theImmediate, recurring));
		Dispatcher<Timer>::GetInst()->addElement(p);
	}
}

void TimerFactory::TimerFired(std::thread::id theThreadId, Timer* t)
{
	std::lock_guard<std::mutex> guard(myMutex);
	myCompletedThreads.push_back(theThreadId);

	// We can't join and delete the thread in this method because it's called from the thread we are trying to delete.
}

void TimerFactory::CreateTimer(std::function<void()>theCallback, uint theInterval, bool theImmediate, bool recurring)
{
	std::lock_guard<std::mutex> guard(myMutex);

	if (myTerminated == true)
	{
		return;
	}

	thread* t = new thread(&TimerFactory::CreateTimerOnThread, theCallback, theInterval, theImmediate, recurring);

	if (recurring)
	{
		t->detach();
		myThreads.push_back(t);
	}

	else if (theImmediate)
	{
		t->join();
	}
	else
	{
		myThreads.push_back(t);
	}
}

void TimerFactory::Clear()
{
	//std::lock_guard<std::mutex> guard(myMutex);

	bool found = false;

	while (myCompletedThreads.size() > 0)
	{
		auto temp2 = (*myCompletedThreads.begin());

		found = false;
		for (auto th = myThreads.begin();
			th != myThreads.end();
			++th)
		{
			if ((*th)->get_id() == temp2)
			{
				(*th)->join();
				auto temp = (*th);
				myThreads.erase(th);
				delete temp;
				
				myCompletedThreads.pop_front();
				found = true;
				break;
			}
		}
	}
}