#include "Timer.h"



Timer::Timer()
{	
	Start();
}


Timer::~Timer()
{}

void Timer::Start()
{
	start = std::chrono::high_resolution_clock::now();	
}

void Timer::Stop()
{
	auto stop = std::chrono::high_resolution_clock::now();
	auto dur = ( stop - start );
	elapse = dur.count();
}

float Timer::GetMilli()
{
	return elapse * 0.000001f;
}
