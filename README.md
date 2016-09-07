# Overview

This is a 3D model of [hexapod](https://en.wikipedia.org/wiki/Hexapod_(robotics)). It's created to test it before building a real robot.

# Build

Program depends only of glut library and generally if you've got it on your platform, you'll not have problems building it.

## Building with cmake

First you'll need to install dependencies. These are: `freeglut3-dev libxi-dev libxmu-dev`. On Ubuntu (12.04 or later) it can be installed by running

	sudo apt-get install freeglut3-dev libxi-dev libxmu-dev

Cmake is used for building. If you don't have it, install using

	sudo apt-get install cmake

To build project run following:

	# create build/ directory
	mkdir -p build
	# enter it
	cd build
	# generating Makefile using cmake
	cmake ..
	# building application
	make

To run use

	./hexapod

in `build/` directory.

## Manual build (without cmake)

Create a build directory and enter it

	mkdir -p build
	cd build/

You will need a `freeglut3-dev` package

	# on Ubuntu
	sudo apt-get install freeglut3-dev

OpenGL and GLU libraries are usually distributed with a compiler collection.

Now compile cpp files (using c++11 standart)

	g++ -c ../src/*.cpp -std=c++11

Now you have all object files. Linking goes as follows (on ubuntu)

	g++ *.o -o hexapod -lGL -lGLU -lglut

If you've done everything correctly, you'll have an executable `./hexapod`.

## Building for other operation systems

### Linux / MacOS

Build freeglut3-dev for your platform (or install it from repositories) and use CMake to build program.

### Cross compile for Windows OS.

You'll need to install [MinGW](http://mingw.org/) or [Cygwin](http://cygwin.com/). Personally I prefer Cygwin cause it emulates Unix environment.

#### Compiling with MinGW

Download the Internet installer for your system (x86/x64) and run it.
You'll need to mark the following packages for installation:

	mingw-gcc-g++
	mingw-make
	mingw-cmake
	mingw-freeglut3-dev
	mingw-OpenGL

#### Compiling with Cygwin

Download the Internet installer for your system (x86/x64) and run it.
You'll need to mark the following packages for installation:

	g++
	make
	cmake
	bash
	freeglut3-dev
	git
	