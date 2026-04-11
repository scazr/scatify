#pragma once
#include <string>
#include <expected>
#include "SDL3/SDL_audio.h"
#include "ErrorHandling/Success/Success.hpp"
#include "ErrorHandling/Failure/DetailedFailure.hpp"
// #include "ErrorHandling/FailureStatus/FileFailure.hpp"
#include "ErrorHandling/FailureStatus/SDLFailure.hpp"

class PlayerWrapper {
  SDL_AudioSpec spec;
  Uint8 *audio_buf = nullptr;
  Uint32 audio_len = 0;
  SDL_AudioDeviceID device = 0;
  SDL_AudioStream *stream = nullptr;

  std::expected<Success, DetailedFailure<SDLFailure>> player_status;

public:
  std::string getSDLError();
  std::expected<Success, DetailedFailure<SDLFailure>> loadSDLSubsystem();
  std::expected<Success, DetailedFailure<SDLFailure>> loadSDLWAV(const std::string &path);
  std::expected<Success, DetailedFailure<SDLFailure>> openSDLAudioDevice();
  void playtest();
  PlayerWrapper(const std::string &audio_file_path);
  ~PlayerWrapper();
};

