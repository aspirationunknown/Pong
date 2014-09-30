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
CXXFLAGS = -O3 -Wall -std=c++11 -g

# OpenGL/Mesa libraries for Linux:
GL_LIBS = -lglut -lGLU -lGL -lm

#-----------------------------------------------------------------------

OBJS = pong.o pongGraphics.o structs.o bmpRead.o


pong: pong.o pongGraphics.o structs.o bmpRead.o 

	g++ ${OBJS} ${CXXFLAGS} -o pong ${GL_LIBS}


bmpRead.o: bmpRead.cpp

	g++ ${CXXFLAGS} -c bmpRead.cpp ${GL_LIBS}


pong.o: pong.cpp pongGraphics.h bmpRead.o

	g++ ${CXXFLAGS} -c pong.cpp ${GL_LIBS}


pongGraphics.o: pongGraphics.cpp pongGraphics.h

	g++ ${CXXFLAGS} -c pongGraphics.cpp ${GL_LIBS}


structs.o: structs.cpp structs.h

	g++ ${CXXFLAGS} -c structs.cpp ${GL_LIBS}

clean:

	rm -rf *o pong
