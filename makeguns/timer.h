#pragma once

class Timer {

private:
  float length, time;
  bool timeout;

public:
  Timer() : length(0), time(0), timeout(false) {};
  Timer(float length);
  void step(float deltaTime);
  float getTime() const;
  float getLength() const;
  bool hasTimedOut() const; // Need a way to check timeout!
  void reset();             // Useful to reset the timer
};