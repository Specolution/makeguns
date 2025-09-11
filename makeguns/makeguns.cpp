// makeguns.cpp : Defines the entry point for the application.
//

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "makeguns.h"

using namespace std;

void cleanup(SDL_Window *win);

int main(int argc, char *argv[]) {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error initializing SDL", nullptr);
    return 1;
  }

  // create the Window
  int width = 800;
  int height = 600;
  SDL_Window *win = SDL_CreateWindow("Make Guns", width, height, 0);

  if (!win) {

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating window", win);
    cleanup(win);
    return 1;
  }

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
      }
    }
  }

  cleanup(win);
  return 0;
}

void cleanup(SDL_Window *win) {
  SDL_DestroyWindow(win);
  SDL_Quit();
}