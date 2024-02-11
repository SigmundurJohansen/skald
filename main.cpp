#pragma warning (disable : 4996)
#include "src/def.h"
#include "src/file_system.h"
#include "src/json_reader.h"
#include "src/makefile.h"
#include <iostream>

const std::string version = "v1.0.0";

int main() {
  make_settings make_settings;
  project project;

  std::cout << "Skald version: " << version;
  project.project_folder = std::filesystem::current_path().string();

  // getting and listing all files needed
  get_project_files(project);
  get_source_files(project);

  std::cout << "----------------------\n";
  std::cout << "Listing project files: \n";
  int ret = 0;
  for (auto str : project.project_files) {
    if (str == "settings.json") {
      std::cout << "\tsettings.json\n";
      ret = get_settings(project);
    }
    if (str == "dependencies.json")
      std::cout << "\tdependencies.json\n";
    if (str == "makefile")
      std::cout << "\tmakefile\n";
  }
  if (ret != 0)
    std::cout << "Error getting settings\n";
  // change folder full path to relative path
  for (auto &relative : project.folders) {
    relative = relative.substr(project.project_folder.size() + 1);
  }

  // change file full path to relative path, for both c and cpp files.
  for (auto &file : project.cpp_files) {
    file = file.substr(project.project_folder.size() + 1);
  }
  for (auto &file : project.c_files) {
    file = file.substr(project.project_folder.size() + 1);
  }

  std::cout << "----------------------\n";
  std::cout << "Listing source files: \n";
  if (!project.cpp_files.empty()) {
    for (auto str : project.cpp_files) {
      std::cout << "\t" << str << "\n";
    }
  }
  if (!project.c_files.empty()) {
    for (auto str : project.c_files) {
      std::cout << "\t" << str << "\n";
    }
  }

  make_settings.compiler_flags.emplace_back(" -g");
  make_settings.compiler_flags.emplace_back(" -Wall");
  make_settings.compiler_flags.emplace_back(" -Wextra");
  make_settings.compiler_flags.emplace_back(" -std=c++17");
  make_settings.compiler_flags.emplace_back(" -fstack-usage");

  std::cout << "----------------------\n";
  std::cout << "Entries in folders: \n";
  for (auto &f : project.folders)
    std::cout << "\t" << f << "\n";
  
  // get dependencies from dependency.json
  std::cout << "----------------------\n";
  std::cout << "Dependencies: \n";
  get_dependencies(project);
  for(auto dep : project.dependencies)
   std::cout << "\t" << dep << "\n"; 
  // locate and manage dependencies using vcpkg

  std::cout << "----------------------\n";
  std::cout << "Generating Makefile: \n";
  generate_makefile(make_settings, project);

  // get settings from settings.json
  // run make file using -j 8
  std::cout << "Skald finished.. " << std::endl;
  return 0;
}
