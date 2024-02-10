#include "src/def.h"
#include "src/file_system.h"
#include "src/makefile.h"
#include <iostream>


int main() {
  make_settings make_settings;
  project project;

  // getting and listing all files needed
  get_project_files(project);
  get_cpp_files(project);

  std::cout << "Listing project files: " << std::endl;
  for (auto str : project.project_files) {
    std::cout << str << std::endl;
    if (str == "settings.json")
      std::cout << "project settings file found" << std::endl;
    if (str == "makefile")
      std::cout << "makefile found" << std::endl;
  }

  std::cout << "Listing cpp files: " << std::endl;
  for (auto str : project.cpp_files) {
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

  /*
  time_function(count);
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::filesystem::path executablePath =
      std::filesystem::canonical("/proc/self/exe");
*/

  // get dependencies from dependency.json
  // locate and manage dependencies using vcpkg

  // get settings from settings.json
  // generate a makefile using cpp files and flags from settings.
  // run make file using -j 8

  return 0;
}
