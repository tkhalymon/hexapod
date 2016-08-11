#!/bin/sh
sudo apt-get install freeglut3-dev libxi-dev libxmu-dev 
mkdir -p build
cd build
cmake ..
make -j 8
./hexapod