CXX:= clang++
CC:= clang

VCPKG_ROOT = D:/tools/vcpkg
VCPKG_TARGET_TRIPLET = x64-linux
INCLUDES = -I$(VCPKG_ROOT)/installed/$(VCPKG_TARGET_TRIPLET)/include
LIBSPATHS = -L$(VCPKG_ROOT)/installed/$(VCPKG_TARGET_TRIPLET)/lib

CFLAGS := -g $(INCLUDES) 
CXXFLAGS := -g -std=c++20 -Wall -fstack-usage $(INCLUDES) 
LDFLAGS := $(LIBSPATHS)
BUILDDIR := build
TARGET := $(BUILDDIR)/skald
C_SRCS := $(wildcard external/yyjson.c)
C_OBJS := $(C_SRCS:%.c=$(BUILDDIR)/%.o)

CPP_SRCS := main.cpp \
	$(wildcard src/json_reader.cpp) \
	$(wildcard src/default_project.cpp) \
	$(wildcard src/makefile.cpp) \
	$(wildcard src/file_system.cpp)

CPP_OBJS := $(CPP_SRCS:%.cpp=$(BUILDDIR)/%.o)

OBJS := $(CPP_OBJS) $(C_OBJS)

all: $(TARGET) 

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	@if [ ! -d "$(BUILDDIR)"]; then mkdir $(@d); fi
	@if [ ! -d "$(BUILDDIR)/src/" ]; then mkdir "$(BUILDDIR)/src/"; fi
	@if [ ! -d "$(BUILDDIR)/external/" ]; then mkdir "$(BUILDDIR)/external/"; fi
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: external/%.c
	$(CC) $(CFLAGS) -c $< -o $@



$(BUILDDIR)/%.o: %.cpp
	@if [ ! -d "$(BUILDDIR)" ]; then mkdir -p $(@D); fi
	@if [ ! -d "$(BUILDDIR)/src" ]; then mkdir -p "$(BUILDDIR)/src"; fi
	@if [ ! -d "$(BUILDDIR)/external" ]; then mkdir -p "$(BUILDDIR)/external"; fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: external/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR)
