// makeguns.cpp : Defines the entry point for the application.
//

#include "makeguns.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h >

using namespace std;

struct SDLState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int width, height, logW, logH;
};

bool initialize(SDLState &state);

void cleanup(SDLState &state);

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
  SDL_Texture *idleTex = IMG_LoadTexture(state.renderer, "data/idle.png");
  SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST);

  // start the game loop
  bool running = true;
  while (running) {

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

    SDL_FRect src{.x = 0, .y = 0, .w = 32, .h = 32};

    SDL_FRect dst{.x = 0, .y = 0, .w = 32, .h = 32};

    SDL_RenderTexture(state.renderer, idleTex, &src, &dst);

    // swap buffers and present
    SDL_RenderPresent(state.renderer);
  }

  SDL_DestroyTexture(idleTex);
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
