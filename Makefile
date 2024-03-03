CXX:= clang++
CC:= clang

CFLAGS := -g 
CXXFLAGS:=-g -Wall -std=c++17 -fstack-usage -Iinclude


TARGET=$(BUILDDIR)/skald
BUILDDIR:= build

C_SRCS:= $(wildcard external/yyjson.c)

CPP_SRCS := main.cpp \
	 $(wildcard src/json_reader.cpp) \
	 $(wildcard src/makefile.cpp) \
	 $(wildcard src/file_system.cpp)


C_OBJS := $(C_SRCS:%.c=$(BUILDDIR)/%.o)

CPP_OBJS := $(CPP_SRCS:%.cpp=$(BUILDDIR)/%.o)

OBJS := $(CPP_OBJS) $(C_OBJS)

all: $(TARGET) copy_libs copy_inclues copy_assets

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	@if [ ! -d "$(BUILDDIR)"]; then mkdir $(@d); fi
	@if [ ! -d "$(BUILDDIR)/src/"]; then mkdir "$(BUILDDIR)/src/"; fi
	@if [ ! -d "$(BUILDDIR)/external/"]; then mkdir "$(BUILDDIR)/external/"; fi
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

copy_libs: 
	@if [ ! -d "$(BUILDDIR)/lib/" ]; then mkdir -p "$(BUILDDIR)/lib/"; fi

copy_inclues: 
	@if [ ! -d "$(BUILDDIR)/external" ]; then mkdir -p "$(BUILDDIR)/external/"; fi

copy_assets: 

clean:
	rm -rf $(BUILDDIR)
