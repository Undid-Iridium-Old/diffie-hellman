# A makefile that canbe used for a generic C++ project in which there is
# a single executable named diffie-hellman, which depends on all source code files.
# To build or update the executable, or any files that require rebuilding,
# type
#     make
# To remove object files only, type
#     make clean
# To remove object files and the executable, type 
#     make cleanall
#
# Written by FrancisIrizarry. 

CXX       := /usr/bin/g++
CXXFLAGS  += -Wall -g -std=c++17 -lm
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
PROG = diffie-hellman


all: $(PROG) 

.PHONY: clean  cleanall
clean:
	rm -f $(OBJS) 

cleanall:
	rm -f $(OBJS) $(PROG) 

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) 

.cpp:
	$(CXX) -c $@.cpp  $(CXXFLAGS)




