# TDisk root Makefile
# Copyright (C) 2026 tigercodes-dev

BUILD_TYPE ?= release

export BUILD_DIR ?= build
export CXX := g++
export CXXFLAGS := -O2 -flto -Wall
export LD := g++
export LDFLAGS := -Wl,-O2 -flto
export LDLIBS :=

ifndef DISABLE_WERROR
export CXXFLAGS += -Werror
endif

ifeq ($(BUILD_TYPE), debug)
export CXXFLAGS += -g
export LDFLAGS += -g
endif

SOURCES := $(shell find src -type f -name '*.cpp')
HEADERS := $(shell find src -type f -name '*.hpp')
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))

.PHONY: all tdisk clean
.SILENT:

all: tdisk

tdisk: build/tdisk

build/tdisk: $(OBJECTS)
	mkdir -p $(@D)
	echo "  CXXLD   $@"
	$(LD) $(LDFLAGS) $^ $(LDLIBS) -o $@
	echo "Your executable is ready: $@"

build/%.o: src/%.cpp $(HEADERS)
	mkdir -p $(@D)
	echo "  CXX     $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*
