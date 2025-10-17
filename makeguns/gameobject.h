#pragma once
#include "animation.h"
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <vector>

enum class PLayerState { idle, running, jumping };

struct PlayerData {
  PLayerState state;
  PlayerData() { state = PLayerState::idle; }
};

struct LevelData {};
struct EnemyData {};

union ObjectData {
  PlayerData player;
  LevelData level;
  EnemyData enemy;
};

enum class ObjectType { player, level, enemy };

struct GameObject {
  ObjectType type;
  ObjectData data;
  glm::vec2 position, velocity, acceleration;
  float direction;
  std::vector<Animation> animations;
  int currentAnimation;
  SDL_Texture *texture;

  GameObject() : data{.level = LevelData()} {
    type = ObjectType::level;
    direction = 1;
    position = velocity = acceleration = glm::vec2(0);
    currentAnimation = -1;
    texture = nullptr;
  }
};