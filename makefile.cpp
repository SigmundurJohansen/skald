#include "makefile.h"

void generate_makefile(make_settings &settings, project &project) {
  // Specify the source file and target executable name
  std::string sourceFile = "main.cpp";
  std::string targetName = "myexecutable";

  // Open a file for writing (or create if it doesn't exist)
  std::ofstream makefile("Makefile");

  // Check if the file is open
  if (makefile.is_open()) {
    // Write the Makefile content
    makefile << "CC := g++\n";
    makefile << "CFLAGS :=";
    for (auto flag : settings.compiler_flags)
      makefile << flag;
    makefile << "\n";
    makefile << "all: " << targetName << "\n";
    makefile << "\n";
    makefile << targetName << ": " << sourceFile;
    for (auto file : project.cpp_files)
      makefile << " " << file;
    makefile << "\n";
    makefile << "\t$(CC) $(CFLAGS) -o $@ $<\n";
    makefile << "\n";
    makefile << "clean:\n";
    makefile << "\trm -f " << targetName << "\n";

    // Close the file
    makefile.close();

    std::cout << "Makefile generated successfully." << std::endl;
  } else {
    std::cerr << "Unable to open Makefile for writing." << std::endl;
  }
}
