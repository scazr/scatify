#pragma once
#include <string>

enum class SDLFailure {
  failure = 1,
  audio_subsystem,
  loading_file,
  opening_device,
  creating_audio_stream,
  binding_audio_stream,
  put_audio_stream_data,
};

inline std::string show(const SDLFailure &file_failure) {
  switch(file_failure) {
    case SDLFailure::failure:
      return "SDLFailure::failure";
    case SDLFailure::audio_subsystem:
      return "SDLFailure::audio_subsystem";
    case SDLFailure::loading_file:
      return "SDLFailure::loading_file";
    case SDLFailure::opening_device:
      return "SDLFailure::opening_device";
    case SDLFailure::creating_audio_stream:
      return "SDLFailure::creating_audio_stream";
    case SDLFailure::binding_audio_stream:
      return "SDLFailure::binding_audio_stream";
    case SDLFailure::put_audio_stream_data:
      return "SDLFailure::put_audio_stream_data";
    default:
      return "SDLFailure::unknown";
  }
}
