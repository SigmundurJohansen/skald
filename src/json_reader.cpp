#include "json_reader.h"
#include "../external/yyjson.h"
#include <cstdlib>
#include <iostream>

int get_settings(project &project) {

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
  yyjson_doc *settings = yyjson_read(data, len, 0);
  if (!settings) {
    std::cout << "Failed to parse JSON.\n";
    free(data);
    return EXIT_FAILURE;
  }
  // Get the root object
  yyjson_val *root = yyjson_doc_get_root(settings);

  // Access the "project_name" value
  yyjson_val *project_name_val = yyjson_obj_get(root, "project_name");
  if (project_name_val) {
    project.project_name = yyjson_get_str(project_name_val);
    std::cout << "Project Name: " << project.project_name << "\n";
  } else {
    std::cout << "The key 'project_name' does not exist.\n";
  }

  std::cout << std::endl;
  // Clean up
  yyjson_doc_free(settings);
  free(settings);

  return EXIT_SUCCESS;
}
