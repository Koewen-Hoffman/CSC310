# Makefile hates me, this does not work even with proper indentation >:(
INCLUDE_DIRS := Includes
CC := g++
CFLAGS := -I$(INCLUDE_DIRS)
OBJS := customErrorClass.o customErrorHandling.o splay.o mainsplay.o
DEPS := $(INCLUDE_DIRS)/customErrorClass.h splay.h

.PHONY: clean all

all: splay

clean:
        rm $(OBJS) splay

customErrorClass.o: customErrorClass.cpp $(DEPS)
        $(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp $(DEPS)
        $(CC) -c -o $@ $(CFLAGS) $<

splay.o: splay.cpp splay.h
        $(CC) -c -o $@ $(CFLAGS) $<

mainsplay.o: mainsplay.cpp splay.h $(DEPS)
        $(CC) -c -o $@ $(CFLAGS) $<

errorTutorial: $(OBJS)
        $(CC) -o $@ $^ $(CFLAGS)