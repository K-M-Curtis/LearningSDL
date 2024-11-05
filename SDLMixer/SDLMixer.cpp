#include <SDL.h>
#include <SDL_mixer.h>

const int CHUNKSIZE = 4096;
const char filename[] = "..\\resource\\audio\\Jaychou-faruxue.mp3";
const char chunk_filename[] = "..\\resource\\audio\\thunder_sound.wav";

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_AUDIO);

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, CHUNKSIZE);

  //Mix_Chunk* sound = Mix_LoadWAV(chunk_filename);
  Mix_Music* music = Mix_LoadMUS(filename);
  if (!music) {
    SDL_Log("Load sound failed: %s\n", Mix_GetError());
    return -1;
  }

  //Mix_PlayChannel(-1, sound, 0);
  Mix_PlayMusic(music, 0);

  SDL_Delay(200000);

  //Mix_FreeChunk(sound);
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();

  return 0;
}