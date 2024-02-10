#include "src/def.h"
#include "src/file_system.h"
#include "src/json_reader.h"
#include "src/makefile.h"
#include <iostream>

int main() {
  make_settings make_settings;
  project project;

  project.project_folder = std::filesystem::current_path().string();

  // getting and listing all files needed
  get_project_files(project);
  get_source_files(project);

  std::cout << "Listing project files: " << std::endl;
  for (auto str : project.project_files) {
    std::cout << str << std::endl;
    if (str == "settings.json") {
      std::cout << "project settings file found" << std::endl;
      get_settings(project);
    }
    if (str == "makefile")
      std::cout << "makefile found" << std::endl;
  }
  // change folder full path to relative path
  for (auto &relative : project.folders) {
    std::cout << relative << std::endl;
    relative = relative.substr(project.project_folder.size() + 1);
    std::cout << relative << std::endl;
  }

  for (auto &file : project.cpp_files) {
    file = file.substr(project.project_folder.size() + 1);
  }
  for (auto &file : project.c_files) {
    file = file.substr(project.project_folder.size() + 1);
  }

  std::cout << "Listing source files: " << std::endl;
  for (auto str : project.cpp_files) {
    std::cout << str << std::endl;
  }
  for (auto str : project.c_files) {
    std::cout << str << std::endl;
  }

  make_settings.compiler_flags.emplace_back(" -g");
  make_settings.compiler_flags.emplace_back(" -Wall");
  make_settings.compiler_flags.emplace_back(" -Wextra");
  make_settings.compiler_flags.emplace_back(" -std=c++17");
  make_settings.compiler_flags.emplace_back(" -fstack-usage");

  generate_makefile(make_settings, project);

  std::cout << "Entries in folders: \n";
  for (auto &f : project.folders)
    std::cout << f << std::endl;

  // get dependencies from dependency.json
  // locate and manage dependencies using vcpkg

  // get settings from settings.json
  // run make file using -j 8

  return 0;
}
