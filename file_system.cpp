#include "file_system.h"
#include <filesystem>
#include <iostream>

void get_project_files(std::vector<std::string> &vector) {
  auto current_file_path = std::filesystem::current_path();
  std::string path = current_file_path.string();
  std::string makefile = "makefile";
  try {
    for (const auto &entry :
         std::filesystem::directory_iterator(current_file_path)) {
      if (entry.is_regular_file()) {
        if (entry.path().extension() == ".json") {
          std::string temp = entry.path().string().substr(path.size() + 1);
          vector.emplace_back(temp);
        }
        if (entry.path().string().find(makefile) != std::string::npos) {
          std::string temp = entry.path().string().substr(path.size() + 1);
          vector.emplace_back(temp);
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "filesystem error, getting project files" << std::endl;
  }
}

void add_cpp_files(std::vector<std::string> &files, std::string path) {
  try {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_regular_file()) {
        if (entry.path().extension() == ".cpp") {
          std::string temp = entry.path().string().substr(path.size() + 1);
          files.emplace_back(temp);
          std::cout << "added new cpp file " << temp << std::endl;
        } else {
          std::cout << "not cpp extension" << std::endl;
        }
      } else {
        std::cout << "not regular file" << std::endl;
      }
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "filesystem error, getting cpp files" << std::endl;
  }
}

void add_folders(std::vector<std::string> &folders, std::string path) {
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_directory()) {
      std::string temp = entry.path().string();
      std::cout << "added new folder " << temp << std::endl;
      folders.emplace_back(temp);
      add_folders(folders, entry.path().string());
    }
  }
}

void get_cpp_files(std::vector<std::string> &vector) {
  auto current_file_path = std::filesystem::current_path();
  std::string path = current_file_path.string();
  std::vector<std::string> folders;

  std::cout << "Starting to add folders" << std::endl;

  add_folders(folders, path);

  std::cout << "Starting to add cpp files from folders" << std::endl;
  for (const auto &folder : folders) {
    std::cout << folder << std::endl;
    add_cpp_files(vector, folder);
  }
}
