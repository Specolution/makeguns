// makeguns.cpp : Defines the entry point for the application.
//

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "makeguns.h"

using namespace std;

int main(int argc, char *argv[]) {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error initializing SDL", nullptr);
  }

  int width = 800;
  int height = 600;
  SDL_Window *win = SDL_CreateWindow("Make Guns", width, height, 0);

  return 0;
}

void cleanup(SDL_Window *win) {
  SDL_DestroyWindow(win);
  SDL_Quit();
}