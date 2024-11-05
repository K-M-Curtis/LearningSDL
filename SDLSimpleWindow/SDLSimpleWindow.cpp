#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("init SDL failed: %s", SDL_GetError());
    return -1;
  }

  // CreateWindow
  SDL_Window* window = SDL_CreateWindow("SimpleWindow", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Log("create window failed %s", SDL_GetError());
    return -1;
  }

  SDL_Delay(5000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}