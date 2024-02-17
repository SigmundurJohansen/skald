#pragma warning(disable : 4996)
#include "src/def.h"
#include "src/file_system.h"
#include "src/json_reader.h"
#include "src/makefile.h"
#include <iostream>

const std::string version = "v1.0.0";

int main(int argc, char *argv[]) {
  make_settings make_settings;
  project project;

  // Iterate through command-line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    // Check for various flags
    if (arg == "-v") {
      project.verbose = true;
    } else {
      std::cerr << "Unknown flag: " << arg << "\n";
      return 1;
    }
  }
  std::cout << "Skald version: " << version << "\n";
  project.project_folder = std::filesystem::current_path().string();

  // getting and listing all files needed
  get_project_files(project);
  get_source_files(project);
  get_settings(project, make_settings);
  get_dependencies(project);
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
  if (project.verbose) {
    std::cout << "----------------------\n";
    std::cout << "Listing project files: \n";
    int ret = 0;
    for (auto str : project.project_files) {
      if (str == "settings.json") {
        std::cout << "\tsettings.json\n";
      }
      if (str == "dependencies.json")
        std::cout << "\tdependencies.json\n";
      if (str == "makefile")
        std::cout << "\tmakefile\n";
    }
    if (ret != 0)
      std::cout << "Error getting settings\n";

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
    std::cout << "----------------------\n";
    std::cout << "Entries in folders: \n";
    for (auto &f : project.folders)
      std::cout << "\t" << f << "\n";
    std::cout << "----------------------\n";
    std::cout << "Dependencies: \n";
    std::cout << "Libraries: \n";
    for (auto dep : project.dependencies)
      std::cout << "\t" << dep << "\n";
    std::cout << "Includes: \n";
    for (auto inc : project.includes)
      std::cout << "\t" << inc << "\n";
    std::cout << "----------------------\n";
    std::cout << "Generating Makefile: \n";
  }
  generate_makefile(make_settings, project);

  // get settings from settings.json
  // run make file using -j 8
  std::cout << "Skald finished.. " << std::endl;
  return 0;
}
