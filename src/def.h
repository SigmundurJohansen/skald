#pragma once
#include <string>
#include <vector>

struct make_settings {
  std::string compiler = "g++";
  std::vector<std::string> compiler_flags;
};

struct project {
  std::string project_name = "foo";
  std::string project_folder = "";
  std::vector<std::string> folders;
  std::vector<std::string> cpp_files;
  std::vector<std::string> c_files;
  std::vector<std::string> project_files;
};
