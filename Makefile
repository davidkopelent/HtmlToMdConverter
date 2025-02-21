# Author: David Kopelent
# Title: Makefile

.PHONY: all compile run check doc clean
.DEFAULT_GOAL = all

## Variables and definitions

CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -Werror -O2 -ggdb
EXECUTABLE = kopeldav
SOURCES := $(filter-out src/ctester.cpp, $(wildcard src/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)
CHECK = valgrind
CHECKFLAGS = --leak-check=full --tool=memcheck --show-leak-kinds=all

## Output colors

BLUE = \033[1;36m
GREEN = \033[1;32m
COLOR_END = \033[0m

## Tasks

all: doc compile

%.o: %.cpp
	@echo "$(BLUE)$^ -> $@$(COLOR_END)"
	$(CXX) -c $(CXXFLAGS) $< -o $@
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp

run: compile
	@./$(EXECUTABLE)

doc: 
	@echo "$(BLUE)Generating documentation:$(COLOR_END)"
	doxygen Doxyfile
	@echo "$(GREEN)Documentation created successfully!$(COLOR_END)"

compile: $(OBJECTS)
	@echo "$(BLUE)Compiling ./$(EXECUTABLE) using '$(CXXFLAGS)' flags:$(COLOR_END)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	@echo "$(GREEN)Compilation successfull!$(COLOR_END)"

check: CXXFLAGS += -g
check: clean compile
	@echo "$(BLUE)Preparing for program check using '$(CHECK)':$(COLOR_END)"
	$(CHECK) @./$(EXECUTABLE) $(CHECKFLAGS)
	@echo "$(GREEN)Ready to check!$(COLOR_END)"

clean:
	@echo "$(BLUE)Removing object files$(COLOR_END)"
	@rm -f -- src/*.o
	@echo "$(BLUE)Removing executables$(COLOR_END)"
	@rm -f $(EXECUTABLE)
	@echo "$(BLUE)Removing documentation$(COLOR_END)"
	@rm -rf -- doc/
	@echo "$(BLUE)Removing converted files$(COLOR_END)"
	@rm -rf examples/HTML/*-converted.*
	@rm -rf examples/HTML/RECURSION/*-converted.*
	@rm -rf examples/MD/*-converted.*
	@rm -rf examples/MD/RECURSION/*-converted.*
	@echo "$(GREEN)Clean successfull!$(COLOR_END)"
