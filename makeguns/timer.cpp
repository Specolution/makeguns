#include "timer.h"

Timer::Timer(float length) : length(length), time(0), timeout(false) {};

bool Timer::step(float deltaTime) {
  timeout = false;
  time += deltaTime;

  if (time >= length) {

    time -= length;
    timeout = true;
    return true;
  }
  return false;
}

float Timer::getTime() const { return time; }

float Timer::getLength() const { return length; }

bool Timer::hasTimedOut() const { return timeout; }

void Timer::reset() {
  time = 0;
  timeout = false;
}