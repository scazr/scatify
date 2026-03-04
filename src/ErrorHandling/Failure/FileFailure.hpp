#pragma once
#include <string>

enum class FileFailure {
  failure = 1,
  inexistent_path,
  not_a_directory,
  not_a_file,
  permission_denied
};

inline std::string show(const FileFailure& file_failure) {
  switch(file_failure) {
    case FileFailure::failure:
      return "FileFailure::failure";
    case FileFailure::inexistent_path:
      return "FileFailure::inexistent_path";
    case FileFailure::not_a_directory:
      return "FileFailure::not_a_directory";
    case FileFailure::not_a_file:
      return "FileFailure::not_a_file";
    case FileFailure::permission_denied:
      return "FileFailure::permission_denied";
    default:
      return "FileFailure::Unknown";
  }
}
