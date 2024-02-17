#include "json_reader.h"
#include "../external/yyjson.h"
#include <cstdlib>
#include <iostream>

int get_settings(project &project, make_settings &make_settings) {
  // read file
  FILE *file = fopen("settings.json", "rb");
  if (!file) {
    std::cout << "Could not Open the file.\n";
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *data = (char *)malloc(len + 1);
  fread(data, 1, len, file);
  data[len] = '\0';
  fclose(file);

  // Parse the JSON file
  yyjson_doc *settings_file = yyjson_read(data, len, 0);
  if (!settings_file) {
    std::cout << "Failed to parse JSON.\n";
    free(data);
    return EXIT_FAILURE;
  }
  // Get the root object
  yyjson_val *root = yyjson_doc_get_root(settings_file);

  // Access the "project_name" value
  yyjson_val *project_name_val = yyjson_obj_get(root, "project_name");
  if (project_name_val) {
    project.project_name = yyjson_get_str(project_name_val);
     if (project.verbose)
    std::cout << "Project Name: " << project.project_name << "\n";
  } else {
    std::cout << "The key 'project_name' does not exist.\n";
  }
  // Access the "debug" value
  yyjson_val *debug_val = yyjson_obj_get(root, "debug");
  if (debug_val) {
    make_settings.compiler_flags.emplace_back("-g");
  } else {
    std::cout << "The key 'debug' does not exist.\n";
  }

  make_settings.compiler_flags.emplace_back(" -Wall");
  // make_settings.compiler_flags.emplace_back(" -Wextra");
  make_settings.compiler_flags.emplace_back(" -std=c++17");
  make_settings.compiler_flags.emplace_back(" -fstack-usage");

  // Clean up
  yyjson_doc_free(settings_file);

  return EXIT_SUCCESS;
}

int get_dependencies(project &project) {
  // read file
  FILE *file = fopen("dependencies.json", "rb");
  if (!file) {
    std::cout << "Could not Open the file.\n";
    return EXIT_FAILURE;
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *data = (char *)malloc(len + 1);
  fread(data, 1, len, file);
  data[len] = '\0';
  fclose(file);

  // Parse the JSON file
  yyjson_doc *dependency_file = yyjson_read(data, len, 0);
  if (!dependency_file) {
    std::cout << "Failed to parse JSON.\n";
    free(data);
    return EXIT_FAILURE;
  }
  // Get the root object
  yyjson_val *root = yyjson_doc_get_root(dependency_file);

  // Access the "vcpkg path" value
  yyjson_val *vcpkg_path_val = yyjson_obj_get(root, "vcpkg_path");
  if (vcpkg_path_val) {
    project.vcpkg_path = yyjson_get_str(vcpkg_path_val);
     if (project.verbose)
    std::cout << "vcpkg path: " << project.vcpkg_path << "\n";
  } else {
    std::cout << "The key 'vcpkg_path' does not exist.\n";
  }

  // Access the "dependencies" value
  yyjson_val *dependency_val = yyjson_obj_get(root, "dependencies");

  size_t dep_idx, dep_max;
  yyjson_val *dep_val;
  yyjson_arr_foreach(dependency_val, dep_idx, dep_max, dep_val) {
    const char *dep = yyjson_get_str(dep_val);
    if (dep) {
      project.dependencies.push_back(std::string(dep));
    }
  }

  yyjson_val *includes_val = yyjson_obj_get(root, "includes");

  size_t include_idx, include_max;
  yyjson_val *include_val;
  yyjson_arr_foreach(includes_val, include_idx, include_max, include_val) {
    const char *inc = yyjson_get_str(include_val);
    if (inc) {
      project.includes.push_back(std::string(inc));
    }
  }
  // Clean up
  yyjson_doc_free(dependency_file);

  return EXIT_SUCCESS;
}