#include "makefile.h"

// Function to replace all backslashes with forward slashes in a string
void replace_forward_slash_with_backslash(std::string &str) {
  for (auto &ch : str) {
    if (ch == '/') {
      ch = '\\';
    }
  }
}

void generate_makefile(make_settings &settings, project &project) {

  std::string vcpkg_path = project.vcpkg_path;
  std::string project_folder = project.project_folder;
#if defined(_WIN32) || defined(_WIN64)
 replace_forward_slash_with_backslash(vcpkg_path);
  replace_forward_slash_with_backslash(project_folder);
#endif
  // Open a file for writing (or create if it doesn't exist)
  std::ofstream makefile("Makefile");
  // Check if the file is open
  if (makefile.is_open()) {
    // Write the Makefile content
    makefile << "CXX:= " + settings.cpp_compiler + "\n";
    makefile << "CC:= " + settings.c_compiler + "\n\n";
    makefile << "CFLAGS := -g \n"; // # Add your C specific flags here
    makefile << "CXXFLAGS:=";
    for (auto flag : settings.compiler_flags)
      makefile << flag;
    makefile << " -I" << project.vcpkg_path << "include\n";
    if (!project.dependencies.empty()) {
      makefile << "LDFLAGS := ";
      makefile << " -L" << project.vcpkg_path << "lib";
      for (auto dep : project.dependencies)
        makefile << " -l" << dep;
    }
    makefile << "\n\n";

    makefile << "TARGET=$(BUILDDIR)/" << project.project_name;
#if defined(_WIN32) || defined(_WIN64)
    makefile << ".exe\n\n";
#else
    {
      makefile << "\n";
      makefile << "BUILDDIR:= build";
      makefile << "\n\n";
    }
#endif
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

    makefile << "all: $(TARGET) copy_libs copy_inclues copy_assets\n\n";

    makefile << "$(TARGET):$(OBJS)\n";
    makefile << "\t$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)\n\n";

    makefile << "$(BUILDDIR)/\%.o: \%.c\n";

#if defined(_WIN32) || defined(_WIN64)
    makefile << "\t@if not exist \"$(BUILDDIR)\" @mkdir $(@D)\n";
    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "\t@if not exist \"$(BUILDDIR)\\" << project.folders[i]
               << "\" mkdir \"$(BUILDDIR)\\" << project.folders[i] << "\"\n";
    }
#else
    makefile << "\t@if [ ! -d \"$(BUILDDIR)\"]; then mkdir $(@d); fi\n";
    for(unsigned int i = 0; i < project.folders.size();i++){
      makefile << "\t@if [ ! -d \"$(BUILDDIR)/" << project.folders[i] << "/\"]; then mkdir \"$(BUILDDIR)/" << project.folders[i] << "/\"; fi\n";
    }
#endif
    
    makefile << "\t$(CC) $(CFLAGS) -c $< -o $@\n\n";

    for (unsigned int i = 0; i < project.folders.size(); i++) {
      makefile << "$(BUILDDIR)/\%.o: " << project.folders[i] << "/\%.c\n";
      makefile << "\t$(CC) $(CFLAGS) -c $< -o $@\n\n";
    }

    makefile << "\n\n";

    makefile << "$(BUILDDIR)/\%.o: \%.cpp\n";

#if defined(_WIN32) || defined(_WIN64)
    makefile << "\t@if not exist \"$(BUILDDIR)\" @mkdir $(@D)\n";
#else
    makefile << "\t@if [ ! -d \"$(BUILDDIR)\" ]; then mkdir -p $(@D); fi\n";
#endif

    for (unsigned int i = 0; i < project.folders.size(); i++) {
#if defined(_WIN32) || defined(_WIN64)
      makefile << "\t@if not exist \"$(BUILDDIR)\\" << project.folders[i]
               << "\" mkdir \"$(BUILDDIR)\\" << project.folders[i] << "\"\n";
#else
      makefile << "\t@if [ ! -d \"$(BUILDDIR)/" << project.folders[i] << "\" ];"
               << " then mkdir -p \"$(BUILDDIR)/" << project.folders[i] << "\"; fi\n";
#endif
    }
    makefile << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n";

    for (unsigned int i = 0; i < project.folders.size(); i++) {
#if defined(_WIN32) || defined(_WIN64)
      makefile << "$(BUILDDIR)/\%.o: " << project.folders[i] << "/\%.cpp\n";
#else
      makefile << "$(BUILDDIR)/%.o: " << project.folders[i] << "/\%.cpp\n";
#endif
      makefile << "\t$(CXX) $(CXXFLAGS) -c $< -o $@\n\n";
    }

    makefile << "copy_libs: \n";

#if defined(_WIN32) || defined(_WIN64)
    makefile << "\t@if not exist \"$(BUILDDIR)/lib\" mkdir \"$(BUILDDIR)/lib\"\n";
#else
    makefile << "\t@if [ ! -d \"$(BUILDDIR)/lib/\" ]; then mkdir -p \"$(BUILDDIR)/lib/\"; fi\n";
#endif

    for (auto dep : project.dependencies) {
#if defined(_WIN32) || defined(_WIN64)
      {
        makefile << "\t@xcopy /q /y /i \"" << vcpkg_path << "bin\\" << dep
                 << ".dll\" $(BUILDDIR)\n";
        makefile << "\t@xcopy /q /y /i \"" << vcpkg_path << "lib\\" << dep
                 << ".lib\" $(BUILDDIR)\\lib\n";
      }
#else
      {
        // makefile << "\tcp \"" << vcpkg_path << "bin/" << dep << ".so\" $(BUILDDIR)\n";
        makefile << "\t@cp \"" << vcpkg_path << "lib/lib" << dep
                 << ".a\" $(BUILDDIR)/lib\n";
      }
    }
#endif
      makefile << "\n";

      makefile << "copy_inclues: \n";

#if defined(_WIN32) || defined(_WIN64)
      makefile << "\t@if not exist \"$(BUILDDIR)/external\" mkdir "
                  "\"$(BUILDDIR)/external\"\n";
#else
      makefile << "\t@if [ ! -d \"$(BUILDDIR)/external\" ]; then mkdir -p \"$(BUILDDIR)/external/\"; fi\n";
#endif
      for (auto inc : project.includes) {
#if defined(_WIN32) || defined(_WIN64)
        makefile << "\t@xcopy /s /e /y /q /d /i  \"" << vcpkg_path
                 << "include\\" << inc << "\" $(BUILDDIR)\\external\\" << inc
                 << "\\\n";
#else
      makefile << "\t@cp -r \"" << vcpkg_path << "include/" << inc
               << "\" $(BUILDDIR)/external/" << inc << "\n";
#endif
      }
      makefile << "\n";

      makefile << "copy_assets: \n";
      for (auto asset : project.assets) {
#if defined(_WIN32) || defined(_WIN64)
        makefile << "\t@xcopy /s /e /y /q /d /i \"" << project_folder << "\\"
                 << asset << "\" \"$(BUILDDIR)\\" << asset << "\"\n";
#else
      makefile << "\t@cp \"" << project_folder << "/" << asset << "/$(BUILDDIR)/"
               << asset << "\"\n";
#endif
      }

      makefile << "\n";      
      makefile << "clean:\n";
#if defined(_WIN32) || defined(_WIN64)
      makefile << "\trmdir /s /q $(BUILDDIR)\n";
#else
      makefile << "\trm -rf $(BUILDDIR)\n";
#endif
      // Close the file
      makefile.close();
      std::cout << "Makefile generated successfully."
                << "\n";
    }
    else {
      std::cerr << "Unable to open Makefile for writing."
                << "\n";
    }
  }
