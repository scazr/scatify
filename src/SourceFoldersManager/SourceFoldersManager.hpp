#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include "ErrorHandling/ReturnStatus/ReturnStatus.hpp"
#include "ErrorHandling/Failure/FileFailure.hpp"

class SourceFoldersManager {
private:
  std::vector<std::filesystem::path> source_folders_path;

public:
  SourceFoldersManager();
  SourceFoldersManager(const std::string &source_folders_path);
  SourceFoldersManager(const std::vector<std::string> &source_folders_path);

  void addDirPath(const std::string &path_str);
  void addDirPaths(const std::vector<std::string> &source_folders_path);

  const std::vector<std::filesystem::path>& getSourceFoldersPaths() const;

  ReturnStatus<FileFailure> verifyDirPath(const std::string &path_str) const;
};

std::string show(const SourceFoldersManager &source_folders_manager);
