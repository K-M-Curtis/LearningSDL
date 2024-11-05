#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FONT_SIZE = 48;
//const char font_path[] = "..\\resource\\font\\hanyihuankaifanti.ttf";
const char font_path[] = "..\\resource\\font\\warmwinter.ttf";

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("init SDL failed: %s\n", SDL_GetError());
    return -1;
  }
  SDL_Window* window = SDL_CreateWindow("SDLUseTTF", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Log("create window failed: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_Log("create renderer failed: %s", SDL_GetError());
    return -1;
  }

  if (TTF_Init() < 0) {
    SDL_Log("init SDL_ttf failed: %s\n", SDL_GetError());
    return -1;
  }

  TTF_Font* font = TTF_OpenFont(font_path, FONT_SIZE);
  if (!font) {
    SDL_Log("load font failed: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Color text_color = {255, 255, 255, 255};
  const char* text = "Hello, SDL_TTF!";
  SDL_Surface* text_surface = TTF_RenderText_Blended(font, text, text_color);

  SDL_Texture* text_texture =
      SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);

  int text_width, text_height;
  TTF_SizeText(font, text, &text_width, &text_height);
  SDL_Rect dst_rect = {100, 100, text_width, text_height};
  SDL_RenderCopy(renderer, text_texture, nullptr, &dst_rect);
  SDL_RenderPresent(renderer);
  SDL_Delay(5000);

  SDL_DestroyTexture(text_texture);
  SDL_DestroyRenderer(renderer);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}