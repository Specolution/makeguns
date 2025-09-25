#pragma once
#include "timer.h"

class Animation {
private:
  Timer timer;
  int frameCount;

public:
  Animation();
  Animation(int frameCount, float length);

  float getLength() const;
  int currentFrame() const;  
  void step(float deltaTime);
};
