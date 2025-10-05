﻿// makeguns.cpp : Defines the entry point for the application.
//

#include "makeguns.h"
#include "gameobject.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h >
#include <array>
#include <string>
#include <vector>

using namespace std;

const size_t LAYER_IDX_LEVEL = 0;
const size_t LAYER_IDX_CHARACTERS = 1;

struct SDLState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int width, height, logW, logH;
};

struct GameState {
  std::array<std::vector<GameObject>, 2> layers;
  int playerIndex;

  GameState() {
    playerIndex = 0; // WILL CHANGE THIS WHEN WE LOAD MAPS
  }
};

struct Resources {
  const int ANIM_PLAYER_IDLE = 0;
  std::vector<Animation> playerAnims;
  std::vector<SDL_Texture *> textures;
  SDL_Texture *texIdle;

  SDL_Texture *loadTexture(SDL_Renderer *renderer,
                           const std::string &filepath) {
    SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.c_str());
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    textures.push_back(tex);
    return tex;
  };

  void load(SDLState &state) {
    playerAnims.resize(5);
    playerAnims[ANIM_PLAYER_IDLE] = Animation(8, 1.6f);

    texIdle = loadTexture(state.renderer, "data/idle.png");
  }

  void unload() {

    for (SDL_Texture *tex : textures) {
      SDL_DestroyTexture(tex);
    }
  }
};

bool initialize(SDLState &state);
void cleanup(SDLState &state);
void drawObject(const SDLState &state, GameState &gs, GameObject &obj,
                float deltaTime);

int main(int argc, char *argv[]) {

  SDLState state;

  state.width = 1600;
  state.height = 900;
  state.logW = 640;
  state.logH = 320;

  if (!initialize(state)) {
    return 1;
  }

  // load game assets

  Resources res;
  res.load(state);

  // setup game data
  GameState gs;

  // create our player
  GameObject player;
  player.type = ObjectType::player;
  player.texture = res.texIdle;
  player.animations = res.playerAnims;
  player.currentAnimation = res.ANIM_PLAYER_IDLE;
  gs.layers[LAYER_IDX_CHARACTERS].push_back(player);

  const bool *keys = SDL_GetKeyboardState(nullptr);
  uint64_t prevTime = SDL_GetTicks();

  // start the game loop
  bool running = true;
  while (running) {

    uint64_t nowTime = SDL_GetTicks();
    float deltaTime = (nowTime - prevTime) / 1000.0f; // convert to seconds
    SDL_Event event{0};
    while (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_EVENT_QUIT: {
        running = false;
        break;
      }

      case SDL_EVENT_WINDOW_RESIZED: {
        state.width = event.window.data1;
        state.height = event.window.data2;
        break;
      }
      }
    }

    // perform drawing commands
    SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
    SDL_RenderClear(state.renderer);

    // draw all objects
    for (auto &layer : gs.layers) {
      for (GameObject &obj : layer) {
        drawObject(state, gs, obj, deltaTime);
      }
    }

    // swap buffers and present
    SDL_RenderPresent(state.renderer);
    prevTime = nowTime;
  }

  res.unload();
  cleanup(state);
  return 0;
}

bool initialize(SDLState &state) {
  bool initSuccess = true;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error initializing SDL", nullptr);
    initSuccess = false;
  }

  // create the Window
  state.window = SDL_CreateWindow("Make Guns", state.width, state.height,
                                  SDL_WINDOW_RESIZABLE);

  if (!state.window) {

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating window", state.window);
    cleanup(state);
    initSuccess = false;
  }

  // create the renderer
  state.renderer = SDL_CreateRenderer(state.window, nullptr);

  if (!state.renderer) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating renderer", state.window);
    initSuccess = false;
  }

  // configure presentation
  SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
  return initSuccess;
}

void cleanup(SDLState &state) {
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  SDL_Quit();
}

void drawObject(const SDLState &state, GameState &gs, GameObject &obj,
                float deltaTime) {

  const float spriteSize = 32;
  SDL_FRect src{.x = 0, .y = 0, .w = 32, .h = 32};

  SDL_FRect dst{
      .x = obj.position.x, .y = obj.position.y - spriteSize, .w = 32, .h = 32};

  SDL_FlipMode flipMode =
      obj.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_RenderTextureRotated(state.renderer, obj.texture, &src, &dst, 0, nullptr,
                           flipMode);
}