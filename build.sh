#!/bin/bash

prefixVar="../qt-dpndncy/lib/cmake"
qtDir="qt-dpndncy"

if [[ ! -d $qtDir ]]; then
	echo -e "Qt Build"

	mkdir $qtDir
	cd $qtDir

	if [[ "$OSTYPE" == "linux-gnu" ]]; then
		./../third-party/qtbase/configure -static -prefix $prefixVar
		cmake --build . --parallel 4
	elif [[ "$OSTYPE" == "msys" ]]; then
		./../third-party/qtbase/configure -static -platform "win32-g++" -no-prefix
		cmake --build .
	fi
fi

cmake -G "Ninja" -B "build" -DCMAKE_PREFIX_PATH=$prefixVar

cd build
cmake --build .