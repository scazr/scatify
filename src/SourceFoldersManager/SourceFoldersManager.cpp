#include "SourceFoldersManager.hpp"
#include "ErrorHandling/io.hpp"

using std::string;
namespace fs = std::filesystem;

SourceFoldersManager::SourceFoldersManager() = default;

SourceFoldersManager::SourceFoldersManager(const string &source_folders_path) {
  SourceFoldersManager::addDirPath(source_folders_path);
};

SourceFoldersManager::SourceFoldersManager(const std::vector<string> &source_folders_path) {
  SourceFoldersManager::addDirPaths(source_folders_path);
};

void SourceFoldersManager::addDirPath(const string &path_str) {
  ReturnStatus<FileFailure> return_status = verifyDirPath(path_str);
  if(!return_status) {
    printcerr(show(return_status));
  }

  source_folders_path.push_back(fs::path{path_str});
}

void SourceFoldersManager::addDirPaths(const std::vector<string> &source_folders_path) {
  if(source_folders_path.empty()) { return ; }

  for(string path : source_folders_path) {
    SourceFoldersManager::addDirPath(path);
  }
}

const std::vector<fs::path> &SourceFoldersManager::getSourceFoldersPaths() const {
  return this->source_folders_path;
}

ReturnStatus<FileFailure> SourceFoldersManager::verifyDirPath(const string &path_str) const {
  fs::path path{path_str};
  std::error_code error_code;

  if(!fs::exists(path, error_code))
    return fail<FileFailure>(FileFailure::inexistent_path, error_code.message());

  if(!fs::is_directory(path, error_code))
    return fail<FileFailure>(FileFailure::not_a_directory, error_code.message());

  // fs::perms permissions = fs::status(path, error_code).permissions();

  fs::directory_iterator it(path, error_code);
  if(error_code)
    return fail<FileFailure>(FileFailure::permission_denied, error_code.message());

  return Success{};
}

std::string show(const SourceFoldersManager &source_folders_manager) {
  string result_string = "";
  for(fs::path path : source_folders_manager.getSourceFoldersPaths()) {
    result_string += path.string() + "\n";
  }

  return result_string;
}
