#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <expected>

#include "ReturnStatus/ReturnStatus.hpp"

using std::string;
namespace fs = std::filesystem;

class SourceFoldersManager {
private:
  std::vector<string> source_folders_path;

public:
  bool addPath(string path_str) {
    source_folders_path.push_back(path_str);
    
    return true;
  }

  ReturnStatus<FileFailure> folderAcessible(const string &path_str) {
    fs::path path{path_str};
    std::error_code error_code;

    if(!fs::exists(path, error_code))
      return fail<FileFailure>(FileFailure::inexistent_path, error_code.message());
    

    if(!fs::is_directory(path, error_code))
      return fail<FileFailure>(FileFailure::not_a_directory, error_code.message());

    return Success{};
  }

};
