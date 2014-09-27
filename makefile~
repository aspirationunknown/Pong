# Makefile for Pong.

# Author: John M. Weiss, Ph.D., Derek Stotz, Charles Parsons
# Written Fall 2014 for CSC433/533 Computer Graphics.

# Usage:  make target1 target2 ...

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
CXXFLAGS = -O3 -Wall -std=c++11

# OpenGL/Mesa libraries for Linux:
GL_LIBS = -lglut -lGLU -lGL -lm

#-----------------------------------------------------------------------

OBJS = game.o pong.o structs.o bmpRead.o


pong: game.o pong.o structs.o bmpRead.o 

	g++ ${OBJS} ${CXXFLAGS} -o pong ${GL_LIBS}


bmpRead.o: bmpRead.cpp

	g++ ${CXXFLAGS} -c bmpRead.cpp ${GL_LIBS}


game.o: game.cpp pong.h bmpRead.o

	g++ ${CXXFLAGS} -c game.cpp ${GL_LIBS}


pong.o: pong.cpp pong.h

	g++ ${CXXFLAGS} -c pong.cpp ${GL_LIBS}


structs.o: structs.cpp pong.h

	g++ ${CXXFLAGS} -c structs.cpp ${GL_LIBS}

clean:

	rm -rf *o pong
