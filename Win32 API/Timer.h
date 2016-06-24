#pragma once
#include <chrono>


class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	float GetMilli();

private:
	std::chrono::high_resolution_clock::time_point start;
	float elapse;
};

