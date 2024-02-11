#include "makefile.h"

void generate_makefile(make_settings &settings, project &project) {
  // Open a file for writing (or create if it doesn't exist)
  std::ofstream makefile("Makefile");
  // Check if the file is open
  if (makefile.is_open()) {
    // Write the Makefile content
    makefile << "CXX:= " + settings.compiler + "\n";
    makefile << "CC := gcc \n\n";
    makefile << "CFLAGS := -g \n"; // # Add your C specific flags here
    makefile << "CXXFLAGS:=";
    for (auto flag : settings.compiler_flags)
      makefile << flag;
    makefile << "\n\n";

    makefile << "TARGET=$(BUILDDIR)/" << project.project_name << "\n\n";

    makefile << "BUILDDIR:= build";
    makefile << "\n\n";

    if (!project.c_files.empty()) {
      makefile << "C_SRCS:= $(wildcard " << project.c_files[0] << ")";
      for (unsigned int i = 1; i < project.c_files.size(); i++) {
        if (i == project.c_files.size() - 1)
          makefile << " \\\n\t $(wildcard " << project.c_files[i] << ")\n";
        else
          makefile << "\t $(wildcard " << project.c_files[i] << ") \\\n";
      }
    }

    makefile << "\n\n";
    makefile << "CPP_SRCS := main.cpp \\\n";
    for (unsigned int i = 0; i < project.cpp_files.size(); i++) {
      if (i == project.cpp_files.size() - 1)
        makefile << "\t $(wildcard " << project.cpp_files[i] << ")\n";
      else
        makefile << "\t $(wildcard " << project.cpp_files[i] << ") \\\n";
    }
    makefile << "\n\n";

    makefile << "C_OBJS := $(C_SRCS:\%.c=$(BUILDDIR)/\%.o)"
             << "\n\n";
    makefile << "CPP_OBJS := $(CPP_SRCS:\%.cpp=$(BUILDDIR)/\%.o)"
             << "\n\n";
    makefile << "OBJS := $(CPP_OBJS) $(C_OBJS)"
             << "\n\n";

    makefile << "all: $(TARGET)\n\n";

    makefile << "$(TARGET):$(OBJS)\n";
    makefile << "\t$(CXX) $(CXXFLAGS) -o $@ $^\n\n";

    makefile << "$(BUILDDIR)/\%.o: \%.c\n";
    makefile << "\t@if not exist \"$(BUILDDIR)\" @mkdir $(@D)\n";
    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "\t@if not exist \"$(BUILDDIR)\\" << project.folders[i]
               << "\" mkdir \"$(BUILDDIR)\\" << project.folders[i] << "\"\n";
    }
    makefile << "\t$(CC) $(CFLAGS) -c $< -o $@\n\n";

    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "$(BUILDDIR)/\%.o: " << project.folders[i] << "/\%.c\n";
      makefile << "\t$(CC) $(CFLAGS) -c $< -o $@\n\n";
    }
    makefile << "\n\n";

    makefile << "$(BUILDDIR)/\%.o: \%.cpp\n";
    makefile << "\t@if not exist \"$(BUILDDIR)\" @mkdir $(@D)\n";
    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "\t@if not exist \"$(BUILDDIR)\\" << project.folders[i]
               << "\" mkdir \"$(BUILDDIR)\\" << project.folders[i] << "\"\n";
    }
    makefile << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n";

    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "$(BUILDDIR)/\%.o: " << project.folders[i] << "/\%.cpp\n";
      makefile << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n";
    }
    makefile << "\n\n";

    makefile << "clean:\n";
    makefile << "\trmdir /s /q $(BUILDDIR)\n";

    // Close the file
    makefile.close();
    std::cout << "Makefile generated successfully." << std::endl;
  } else {
    std::cerr << "Unable to open Makefile for writing." << std::endl;
  }
}
