#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// init SDL and CreateWindow
void Init(const char *title, int width, int height, SDL_Window **window) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("init SDL failed: %s", SDL_GetError());
    exit(-1);
  }
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP);

  *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!(*window)) {
    SDL_Log("create window failed: %s", SDL_GetError());
    exit(-1);
  }

  //使用texture，要把这里注释掉，不然会报错，报window已经有关联surface
  //*win_surface = SDL_GetWindowSurface(*window);
  //if (!(*win_surface)) {
  //  SDL_Log("get window surface failed: %s", SDL_GetError());
  //  exit(-1);
  //}
}

SDL_Surface *LoadSurface(const char *filename) {
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface) {
    SDL_Log("Load Image %s failed: %s\n", filename, SDL_GetError());
    return nullptr;
  }
  return surface;
}

// destroy
void Clear(SDL_Window **window) {
  SDL_DestroyWindow(*window);
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  SDL_Window *window = nullptr;
  Init("SDLTexture", SCREEN_WIDTH, SCREEN_HEIGHT, &window);

  bool quit = false;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_Log("create renderer failed: %s", SDL_GetError());
    return -1;
  }
  SDL_Surface *image_surface = LoadSurface("../resource/picture/flower.jpeg");
  if (!image_surface) {
    SDL_Log("surface load failed: %s", SDL_GetError());
    SDL_FreeSurface(image_surface);
    Clear(&window);
    return -1;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);
  if (!texture) {
    SDL_Log("create texture failed: %s", SDL_GetError());
    return -1;
  }

  while (!quit) {
    static SDL_Event ev = {0};
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) {
        quit = true;
      }
    }

    // 绘制一条对角线
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 640, 480);

    // 绘制填充矩形
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    SDL_Rect rect = {100, 100, 300, 300};
    SDL_RenderFillRect(renderer, &rect);

    // 通过texture显示图片
    SDL_Rect src_rect = {50, 50, 100, 100};
    SDL_Rect dst_rect = {20, 0, 200, 200};
    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
    SDL_RenderPresent(renderer);
  }

  //SDL_DestroyTexture(texture);
  SDL_FreeSurface(image_surface);
  SDL_DestroyRenderer(renderer);
  Clear(&window);
  return 0;
}