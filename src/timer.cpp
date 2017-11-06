#include <timer.hpp>

Timer::Timer() {}

void Timer::add_time(float additional_time) {
	time+=additional_time;
}
void Timer::restart_time() {
	time=0;
}
float Timer::get_time() {
	return time;
}
