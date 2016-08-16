#!/bin/bash
declare -a PACKAGES=("freeglut3-dev" "libxi-dev" "libxmu-dev")

for PKG in ${PACKAGES[@]}; do
	if [ "$(dpkg -s $PKG | grep -e 'Status')" != "Status: install ok installed" ]; then
		echo "Installing $PKG package"
		sudo apt-get install $PKG
	else
		echo "Package $PKG is installed"
	fi
done
mkdir -p build
cd build
cmake ..
make -j 8
./hexapod