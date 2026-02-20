#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_error.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <filesystem>
#include <ostream>

int main() {
  if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error loading audio subsystem: " << SDL_GetError() << '\n';
    return 1;
  }

  SDL_AudioSpec spec;
  Uint8 *audio_buf = nullptr;
  Uint32 audio_len = 1024;

  std::cout << std::filesystem::current_path() << std::endl;

  bool status_LoadWAV = SDL_LoadWAV("src/sample.wav", &spec, &audio_buf, &audio_len);
  if(!status_LoadWAV) {
    std::cerr << "Error loading wav file: " << SDL_GetError() << '\n';
    return 1;
  }

  SDL_AudioDeviceID dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
  if(!dev) {
    std::cerr << "Error opening device: " << SDL_GetError() << '\n';
    return 1;
  }

  SDL_AudioStream *stream = SDL_CreateAudioStream(&spec, &spec);
  if(!stream) {
    std::cerr << "Error creating audio stream: " << SDL_GetError() << '\n';
    return 1;
  }

  SDL_BindAudioStream(dev, stream);

  SDL_PutAudioStreamData(stream, audio_buf, audio_len);

  SDL_ResumeAudioDevice(dev);

  SDL_Delay(10000);

  SDL_DestroyAudioStream(stream);
  SDL_CloseAudioDevice(dev);
  SDL_free(audio_buf);




  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* win = SDL_CreateWindow("SDL3 Cross Build", 800, 600, 0);
  SDL_Delay(2000);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
