#ifndef TIMERHPP
#define TIMERHPP

#include <common.hpp>

class Timer{
	float time=0;
public:
	Timer();

	void update(float dTime);
	void Restart();
	float Get();
};

#endif//TIMERHPP
