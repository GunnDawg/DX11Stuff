#pragma once
#include <chrono>

class Benchmarker
{
public:
	Benchmarker()
	{
		StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Benchmarker()
	{
		Stop();
	}

	void Stop()
	{
		auto EndTimePoint = std::chrono::high_resolution_clock::now();
		auto Start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimePoint).time_since_epoch().count();
		auto End = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();
		auto Duration = End - Start;
		double ms = Duration * 0.001;

		printf("%f ms\n", ms);
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> StartTimePoint;
};