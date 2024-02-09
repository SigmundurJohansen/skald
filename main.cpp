#include "def.h"
#include "example/src/util.h"
#include "file_system.h"
#include "makefile.h"
#include <filesystem>
#include <iostream>

int main() {
  make_settings make_settings;
  project project;

  // getting and listing all files needed
  get_project_files(project.project_files);
  get_cpp_files(project.cpp_files);

  for (auto str : project.project_files) {
    std::cout << str << std::endl;
    if (str == "settings.json")
      std::cout << "project settings file found" << std::endl;
    if (str == "makefile")
      std::cout << "makefile found" << std::endl;
  }

  for (auto str : project.cpp_files) {
    std::cout << str << std::endl;
  }

  make_settings.compiler_flags.emplace_back(" -Wall");
  make_settings.compiler_flags.emplace_back(" -Wextra");
  make_settings.compiler_flags.emplace_back(" -std=c++20");
  make_settings.compiler_flags.emplace_back(" -fstack-usage");
  // make_settings.compiler_flags.emplace_back(" -Wundef");

  generate_makefile(make_settings, project);

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
