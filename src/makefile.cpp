#include "makefile.h"

void generate_makefile(make_settings &settings, project &project) {
  // Specify the source file and target executable name
  std::string targetName = "myexecutable";

  // Open a file for writing (or create if it doesn't exist)
  std::ofstream makefile("Makefile");

  // Check if the file is open
  if (makefile.is_open()) {
    // Write the Makefile content
    makefile << "CXX:= " + settings.compiler + "\n\n";

    makefile << "CXXFLAGS:=";
    for (auto flag : settings.compiler_flags)
      makefile << flag;
    makefile << "\n\n";

    makefile << "TARGET=" << project.project_name << "\n\n";

    /*
    SRCDIR := src
    BUILDDIR := build
    */

    makefile << "SRCDIR:=";
    for (auto folder : project.folders)
      makefile << " " << folder;

    makefile << "\n\n";
    makefile << "BUILDDIR:= build";
    makefile << "\n\n";

    makefile << "SRCS=main.cpp";
    for (auto file : project.cpp_files)
      makefile << " $(SRCDIR)/" << file;
    makefile << "\n\n";

    makefile << "OBJS:=$(patsubst %,$(BUILDDIR)/%,$(notdir $(SRCS:.cpp=.o)))"
             << "\n\n";

    makefile << "vpath %.cpp $(SRCDIR):.\n\n";

    makefile << "all: $(TARGET)\n\n";

    makefile << "$(TARGET):$(OBJS)\n";
    makefile << "\t$(CXX) $(CXXFLAGS) -o $@ $^\n\n";

    makefile << "$(BUILDDIR)/"
             << "%."
             << "o: "
             << "%."
             << "cpp\n";
    makefile << "\t@if not exist \"$(BUILDDIR)\" @mkdir $(@D)\n";
    makefile << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n";

    makefile << "clean:\n";
    makefile << "\trmdir /s /q $(BUILDDIR).exe\n";

    // Close the file
    makefile.close();

    std::cout << "Makefile generated successfully." << std::endl;
  } else {
    std::cerr << "Unable to open Makefile for writing." << std::endl;
  }
}
