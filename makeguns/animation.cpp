#include "animation.h"

Animation::Animation() : timer(0), frameCount(0) {}

Animation::Animation(int frameCount, float length)
    : frameCount(frameCount), timer(length) {}

float Animation::getLength() const { return timer.getLength(); }
int Animation::currentFrame() const {
  return static_cast<int>(timer.getTime() / timer.getLength() * frameCount);
}

void Animation::step(float deltaTime) { timer.step(deltaTime); };
