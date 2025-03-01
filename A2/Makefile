# Makefile hates me, this does not work even with proper indentation >:(
INCLUDE_DIRS := Includes
CC := g++
CFLAGS := -I$(INCLUDE_DIRS)
OBJS := customErrorClass.o dsw.o main.o
DEPS := $(INCLUDE_DIRS)/customErrorClass.h dsw.h

.PHONY: clean all

all: $(OBJS)

clean: rm $(OBJS) mainOutput

customErrorClass.o: $(INCLUDE_DIRS)/customErrorClass.cpp $(DEPS) $(CC) -c -o $@ $(CFLAGS) $<

dsw.o: dsw.cpp $(DEPS) $(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp $(DEPS) $(CC) -c -o $@ $(CFLAGS) $<

mainOutput: $(OBJS) $(CC) -o $@ $^ $(CFLAGS)