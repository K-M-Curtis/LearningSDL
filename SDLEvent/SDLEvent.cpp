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

SDL_Surface *LoadSurface(const char *filename) {
  SDL_Surface *surface = SDL_LoadBMP(filename);
  if (!surface) {
    SDL_Log("Load Image %s failed: %s\n", filename, SDL_GetError());
    return nullptr;
  }
  return surface;
}

// destroy
void Clear(SDL_Window **window) {
  SDL_DestroyWindow(*window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  SDL_Window *window = nullptr;
  SDL_Surface *window_surface = nullptr;
  Init("SDLEvent", SCREEN_WIDTH, SCREEN_HEIGHT, &window,
       &window_surface);

  bool quit = false;
  int x = 0, y = 0;
  int num = 0;
  // only load .bmp file
  SDL_Surface *image_surface = LoadSurface("../resource/picture/tank.bmp");
  if (!image_surface) {
    SDL_Log("surface load failed: %s", SDL_GetError());
    SDL_FreeSurface(image_surface);
    Clear(&window);
    return -1;
  }

  while (!quit) {
    static SDL_Event ev = {0};
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) {
        quit = true;
      } else if (ev.type == SDL_KEYDOWN) {
        // KeyEvent
        switch (ev.key.keysym.sym) {
          case SDLK_UP:
            y--;
            break;
          case SDLK_DOWN:
            y++;
            break;
          case SDLK_LEFT:
            x--;
            break;
          case SDLK_RIGHT:
            x++;
            break;
          default:
            x = 0;
            y = 0;
            break;
        }
      }
    }

    // �����ƶ���ǿ�汾  SDL_GetKeyboardState����
    // ��ȡ���̵�ǰ״̬�Ŀ��ա����ص�ָ����һ��ָ���ڲ� SDL�����ָ�롣
    // ������Ӧ�ó��������������������Ч����Ӧ�ñ��������ͷš�
    // ֵΪ1������Ԫ�ر�ʾ�ü��Ѱ��£�ֵΪ0�ı�ʾ�ü�δ���¡���������������ʹ��
    // SDL_Scancodeֵ��ʹ��SDL_PumpEvents ����״̬���顣
    if (SDL_GetKeyboardState(&num)[SDL_SCANCODE_UP]) {
      y--;
    }
    if (SDL_GetKeyboardState(&num)[SDL_SCANCODE_DOWN]) {
      y++;
    }
    if (SDL_GetKeyboardState(&num)[SDL_SCANCODE_LEFT]) {
      x--;
    }
    if (SDL_GetKeyboardState(&num)[SDL_SCANCODE_RIGHT]) {
      x++;
    }

    // clear screen or fill window_surface
    SDL_FillRect(window_surface, NULL, 0xffff);
    SDL_Rect position_rect = {x, y, 0, 0};
    // show image
    SDL_BlitSurface(image_surface, NULL, window_surface, &position_rect);
    SDL_UpdateWindowSurface(window);
  }

  SDL_FreeSurface(image_surface);
  Clear(&window);
  return 0;
}