#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// init SDL and CreateWindow
void Init(const char *title, int width, int height, SDL_Window **window,
          SDL_Surface **win_surface) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("init SDL failed: %s", SDL_GetError());
    exit(-1);
  }

  *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!(*window)) {
    SDL_Log("create window failed: %s", SDL_GetError());
    exit(-1);
  }

  *win_surface = SDL_GetWindowSurface(*window);
  if (!(*win_surface)) {
    SDL_Log("get window surface failed: %s", SDL_GetError());
    exit(-1);
  }
}

// destroy
void clear(SDL_Window **window) {
  SDL_DestroyWindow(*window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  SDL_Window *window = nullptr;
  SDL_Surface *window_surface = nullptr;
  Init("SDLDisplayPicture", SCREEN_WIDTH, SCREEN_HEIGHT, &window,
       &window_surface);

  // only load .bmp file
  SDL_Surface *surface = SDL_LoadBMP("./resource/SDLDisplayPicture/tank.bmp");
  if (!surface) {
    SDL_Log("surface load failed: %s", SDL_GetError());
  } else {
    // cout the format
    SDL_Log("surface format: %d", surface->format->format);
    SDL_Log("surface format: %s",
            SDL_GetPixelFormatName(surface->format->format));
    SDL_Log("window_surface format: %s",
            SDL_GetPixelFormatName(window_surface->format->format));
    // convert the pic format
    surface = SDL_ConvertSurface(surface, window_surface->format, 0);
    SDL_Log("After convert the surface format: %s",
            SDL_GetPixelFormatName(surface->format->format));
    SDL_Log("The surface size width: %d, height: %d", surface->w, surface->h);
    // modify the pic pixels
    Uint32 *pixels = (Uint32 *)surface->pixels;
    for (int i = 0; i < 500; i++) {
      pixels[i] = 0xff00ff;  // SDL_MapRGBA(surface->format, 255, 0, 0, 255);
    }

    // output the dst coordinates
    SDL_Rect dst_rect = {20, 20, 0, 0};
    // output the pic coordinates
    SDL_Rect scale_rect = {10, 10, 500, 400};
    SDL_BlitSurface(surface, &scale_rect, window_surface, &dst_rect);
  }
  SDL_UpdateWindowSurface(window);
  SDL_Delay(5000);
  SDL_FreeSurface(surface);
  clear(&window);
  return 0;
}