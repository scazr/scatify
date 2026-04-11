#include <SDL3/SDL.h>
#include "SourceFoldersManager/SourceFoldersManager.hpp"
#include <iostream>
// #include <filesystem>
#include "PlayerWrapper.hpp"

int main() {
  PlayerWrapper player = PlayerWrapper("src/sample.wav");
  player.playtest();

  SourceFoldersManager source_folders_manager = SourceFoldersManager();
  source_folders_manager.addDirPath("C:/Users/Guilherme/Music");
  source_folders_manager.addDirPath("C:/Users/Guilherme/Desktop");

  std::cout << show(source_folders_manager);

  // SDL_Delay(10000);

  // SDL_DestroyAudioStream(stream);
  // SDL_CloseAudioDevice(dev);
  // SDL_free(audio_buf);




 
  // SDL_Window* win = SDL_CreateWindow("SDL3 Cross Build", 800, 600, 0);
  // SDL_Delay(2000);
  // SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
