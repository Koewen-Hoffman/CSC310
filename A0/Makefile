# I had to so a bit of searching around for how I should do this
# This is not working for me, this is my attempt at using makefile
# I had just made a batch file for compiling because I am so confused on how to get this to work
INCLUDE_DIRS := include
CC 			 := g++
CFLAGS 		 := -I./$(INCLUDE_DIRS)
TARGET		 := mainP # Name of executable, for no confusion
SOURCES		 := $(INCLUDE_DIRS)/bstP.cpp $(INCLUDE_DIRS)/customErrorClass.cpp mainP.cpp

OBJS 		 := $(SOURCES:.cpp=.o)
DEPS 		 := $(INCLUDE_DIRS)/customErrorClass.h $(INCLUDE_DIRS)/bstP.h

.PHONY: clean all run

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)