#include "timer.h"

Timer::Timer(float length) : length(length), time(0) {}

void Timer::step(float deltaTime) {
  timeout = false;
  time += deltaTime;

  if (time >= length) {

    time -= length;
    timeout = true;
  }
}

bool Timer::hasTimedOut() const { return timeout; }

void Timer::reset() {
  time = 0;
  timeout = false;
}