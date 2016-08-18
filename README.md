## Overview

This is a 3D model of [hexapod](https://en.wikipedia.org/wiki/Hexapod_(robotics)). It's created ot test it before building a real robot.

## Build

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
