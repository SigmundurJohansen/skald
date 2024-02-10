#include "file_system.h"
#include <iostream>

std::vector<std::string> exempt_folders = {".git", "build", ".vscode"};

void get_project_files(project &project) {
  auto current_file_path = std::filesystem::current_path();
  std::string path = current_file_path.string();
  std::string makefile = "makefile";
  try {
    for (const auto &entry :
         std::filesystem::directory_iterator(current_file_path)) {
      if (entry.is_regular_file()) {
        if (entry.path().extension() == ".json") {
          std::string temp = entry.path().string().substr(path.size() + 1);
          project.project_files.emplace_back(temp);
        }
        if (entry.path().string().find(makefile) != std::string::npos) {
          std::string temp = entry.path().string().substr(path.size() + 1);
          project.project_files.emplace_back(temp);
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "Filesystem error: getting project files" << std::endl;
  }
}

// Function to replace all backslashes with forward slashes in a string
void replaceBackslashWithForwardSlash(std::string &str) {
  for (auto &ch : str) {
    if (ch == '\\') {
      ch = '/';
    }
  }
}

void add_cpp_files(std::vector<std::string> &files, std::string path) {
  try {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_regular_file()) {
        if (entry.path().extension() == ".cpp") {
          std::string temp = entry.path().string();
          replaceBackslashWithForwardSlash(temp);
          files.emplace_back(temp);
          std::cout << "Added file: " << temp << std::endl;
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "filesystem error, getting files" << std::endl;
  }
}

void add_c_files(std::vector<std::string> &files, std::string path) {
  try {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_regular_file()) {
        if (entry.path().extension() == ".c" && entry.path().extension() != ".cpp") {
          std::string temp = entry.path().string();
          replaceBackslashWithForwardSlash(temp);
          files.emplace_back(temp);
          std::cout << "Added file: " << temp << std::endl;
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << "filesystem error, getting files" << std::endl;
  }
}

bool contains(const std::vector<std::string> &list, const std::string &target) {
  for (const auto &item : list) {
    if (item == target) {
      return true; // Found a match
    }
  }
  return false; // No match found
}

void add_folders(std::vector<std::string> &folders, std::string path) {
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_directory()) {
      std::string temp = entry.path().filename().string();
      if (contains(exempt_folders, temp)) {
      } else {
        std::cout << "Added new folder: " << temp << std::endl;
        std::string full_path = entry.path().string();
        folders.emplace_back(full_path);
        add_folders(folders, full_path);
      }
    }
  }
}

void get_source_files(project &project) {
  auto current_file_path = std::filesystem::current_path();
  std::string path = current_file_path.string();
  std::cout << "Starting to add folders" << std::endl;
  add_folders(project.folders, path);
  std::cout << "Starting to add cpp files from folders" << std::endl;
  for (const auto &folder : project.folders) {
    std::cout << folder << std::endl;
    add_cpp_files(project.cpp_files, folder);
    add_c_files(project.c_files, folder);
  }
}
