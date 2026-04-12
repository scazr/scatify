#include <expected>
#include "PlayerWrapper.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_audio.h"
#include "ErrorHandling/FailureStatus/SDLFailure.hpp"
#include "ErrorHandling/io.hpp"

using std::string;

PlayerWrapper::PlayerWrapper(const string &audio_file_path) {
  if(!loadSDLSubsystem())
    return;

  if(!loadSDLWAV(audio_file_path))
    return;

  if(!openSDLAudioDevice())
    return;

  if(!createSDLAudioStream())
    return;

  if(!bindAudioStreamSDL())
    return;
 
  if(!putAudioStreamDataSDL())
    return;
}

PlayerWrapper::~PlayerWrapper() {
  if(stream)
    SDL_DestroyAudioStream(stream);
  if(device)
    SDL_CloseAudioDevice(this->device);
  if(audio_buf)
    SDL_free(audio_buf);
}

string PlayerWrapper::getSDLError() {
  return string(SDL_GetError());
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::loadSDLSubsystem() {
  if(!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    string error_description = "Error loading audio subsystem: " + getSDLError();

    printcerr(error_description);

    auto error = std::unexpected(
      fail(SDLFailure::audio_subsystem, error_description)
    );
    this->player_status = error;

    return error;
  }

  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::loadSDLWAV(const string &path) {
  bool wav_load_success = SDL_LoadWAV(
    path.c_str(),
    &this->spec,
    &this->audio_buf,
    &this->audio_len
  );
  if(!wav_load_success) {
    string error_description = "Error loading wav file: " + getSDLError();

    printcerr(error_description);

    std::unexpected error = std::unexpected(
      fail(SDLFailure::loading_file, error_description)
    );
    this->player_status = error;

    return error;
  }

  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::openSDLAudioDevice() {
  this->device = SDL_OpenAudioDevice(
    SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
    &this->spec
  );
  if(!this->device) {
    string error_description = "Error opening device: " + getSDLError();

    printcerr(error_description);

    auto error = std::unexpected(
      fail(SDLFailure::opening_device, error_description)
    );
    this->player_status = error;

    return error;
  }

  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::createSDLAudioStream() {
  this->stream = SDL_CreateAudioStream(&this->spec, &this->spec);
  if(!this->stream) {
    string error_description = "Error creating audio stream: " + getSDLError();

    printcerr(error_description);

    auto error = std::unexpected(
      fail(SDLFailure::creating_audio_stream, error_description)
    );
    this->player_status = error;

    return error;
  }
  
  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::bindAudioStreamSDL() {
  if(!this->device || !this->stream) {
    string error_description = "Error, invalid device or stream";

    printcerr(error_description);

    auto error = std::unexpected(
      fail(SDLFailure::binding_audio_stream, error_description)
    );
    this->player_status = error;

    return error;
  }

  if(!SDL_BindAudioStream(this->device, this->stream)) {
    string error_description = "Error binding audio stream: " + getSDLError();

    printcerr(error_description);

    auto error = std::unexpected(
      fail(SDLFailure::binding_audio_stream, error_description)
    );
    this->player_status = error;

    return error;
  }

  return succeed();
}

std::expected<Success, DetailedFailure<SDLFailure>>
PlayerWrapper::putAudioStreamDataSDL() {
  if(!SDL_PutAudioStreamData(this->stream, this->audio_buf, this->audio_len)) {
    string error_description = "Error putting audio stream data: " + getSDLError();

    printcerr(error_description);

    auto failure = std::unexpected(
      fail(SDLFailure::put_audio_stream_data, error_description)
    );

    this->player_status = failure;

    return failure;
  }

  return succeed();
}


void PlayerWrapper::play() {
  SDL_ResumeAudioDevice(this->device);
}

void PlayerWrapper::playtest() {
  if(!this->device || !this->stream || !this->audio_buf) return;

  SDL_BindAudioStream(this->device, this->stream);

  SDL_PutAudioStreamData(this->stream, this->audio_buf, this->audio_len);

  SDL_ResumeAudioDevice(this->device);
}
