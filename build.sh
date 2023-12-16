#!/bin/bash

prefixVar="C:/qt6/qt6-build/qtbase/lib/cmake"
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

cmake -G "MinGW Makefiles" -B "build" -DCMAKE_PREFIX_PATH=$prefixVar

cd build
cmake --build .