CXX:= g++
CC:= gcc

VCPKG_ROOT = D:\tools\vcpkg
VCPKG_TARGET_TRIPLET = x64-windows
INCLUDES = -I$(VCPKG_ROOT)/installed/$(VCPKG_TARGET_TRIPLET)/include
LIBSPATHS = -L$(VCPKG_ROOT)/installed/$(VCPKG_TARGET_TRIPLET)/lib

CFLAGS := -g $(INCLUDES) 
CXXFLAGS := -g -std=c++17 -Wall -fstack-usage $(INCLUDES) 
LDFLAGS := $(LIBSPATHS)
BUILDDIR := build
TARGET := $(BUILDDIR)/skald.exe

C_SRCS := $(wildcard external/yyjson.c)
C_OBJS := $(C_SRCS:%.c=$(BUILDDIR)/%.o)

CPP_SRCS :=
	$(wildcard src/main.cpp) \
	$(wildcard src/default_project.cpp) \
	$(wildcard src/file_system.cpp) \
	$(wildcard src/json_reader.cpp) \
	$(wildcard src/makefile.cpp)

CPP_OBJS := $(CPP_SRCS:%.cpp=$(BUILDDIR)/%.o)

OBJS := $(CPP_OBJS) $(C_OBJS)

all: $(TARGET) 

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	@if not exist "$(BUILDDIR)" @mkdir $(@D)
	@if not exist "$(BUILDDIR)/external" mkdir "$(BUILDDIR)/external"
	@if not exist "$(BUILDDIR)/src" mkdir "$(BUILDDIR)/src"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: external/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@



$(BUILDDIR)/%.o: %.cpp
	@if not exist "$(BUILDDIR)" @mkdir $(@D)
	@if not exist "$(BUILDDIR)/external" mkdir "$(BUILDDIR)/external"
	@if not exist "$(BUILDDIR)/src" mkdir "$(BUILDDIR)/src"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: external/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)

clean:
	rmdir /s /q $(BUILDDIR)
