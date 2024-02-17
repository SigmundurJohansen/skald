#pragma once
#include <string>
#include <vector>

struct make_settings {
  std::string cpp_compiler = "clang++";
  std::string c_compiler = "clang";
  std::vector<std::string> compiler_flags;
};

struct project {
  std::string project_name = "foo";
  std::string project_folder = "";
  bool verbose = false;
  std::string vcpkg_path;
  std::vector<std::string> folders;
  std::vector<std::string> cpp_files;
  std::vector<std::string> c_files;
  std::vector<std::string> project_files;
  std::vector<std::string> dependencies;
  std::vector<std::string> includes;
  std::vector<std::string> assets;
};
