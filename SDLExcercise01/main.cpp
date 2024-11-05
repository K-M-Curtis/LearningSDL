#include <SDL.h>

int main(int argc, char* argv[]) {
  // init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("init SDL failed: %s", SDL_GetError());
    return -1;
  }

  return 0;
}