#include <iostream>
#include "PlayerWrapper.hpp"
#include "ErrorHandling/io.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_timer.h"

using std::string;
using std::unexpected;

string PlayerWrapper::getSDLError() {
  return string(SDL_GetError());
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::loadSDLSubsystem() {
  if(!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    string error_description = "Error loading audio subsystem: " + getSDLError();
    printcerr(error_description);
    unexpected error = unexpected(fail(SDLFailure::audio_subsystem, error_description));
    this->player_status = error;
    return error;
  }
  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::loadSDLWAV(const string &path) {
  bool wav_load_success = SDL_LoadWAV(path.c_str(), &this->spec, &this->audio_buf, &this->audio_len);
  if(!wav_load_success) {
    string error_description = "Error loading wav file: " + getSDLError();
    printcerr(error_description);
    unexpected error = unexpected(fail(SDLFailure::loading_file, error_description));
    this->player_status = error;
    return error;
  }
  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::openSDLAudioDevice() {
  SDL_AudioDeviceID dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &this->spec);
  if(!dev) {
    string error_description = "Error opening device:" + getSDLError();
    printcerr(error_description);
    unexpected error = unexpected(fail(SDLFailure::opening_device, error_description));
    this->player_status = error;
    return error;
  }
  return succeed();
}

void PlayerWrapper::playtest() {
  if(!this->device || !this->stream || !this->audio_buf)
    return;

  SDL_BindAudioStream(this->device, this->stream);

  SDL_PutAudioStreamData(this->stream, this->audio_buf, this->audio_len);

  SDL_ResumeAudioDevice(this->device);
 

  SDL_Delay(10000);

}

PlayerWrapper::PlayerWrapper(const string &audio_file_path) {
  std::expected<Success, DetailedFailure<SDLFailure>> audio_subsystem_status = loadSDLSubsystem();
  if(!audio_subsystem_status) return;

  std::expected<Success, DetailedFailure<SDLFailure>> audio_file_status = loadSDLWAV(audio_file_path);
  if(!audio_file_status) return;

  this->device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &this->spec);
  if(!this->device) {
    string error_description = "Error opening device:" + getSDLError();
    printcerr(error_description);
    this->player_status = unexpected(fail(SDLFailure::opening_device, error_description));
  }

  this->stream = SDL_CreateAudioStream(&this->spec, &this->spec);
  if(!stream) {
    std::cerr << "Error creating audio stream: " << SDL_GetError() << '\n';
  }
}

PlayerWrapper::~PlayerWrapper() {
  if(stream)
    SDL_DestroyAudioStream(stream);
  if(device)
    SDL_CloseAudioDevice(this->device);
  if(audio_buf)
    SDL_free(audio_buf);
}


