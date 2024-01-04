#!/bin/bash

cd "third-party"
git clone https://code.qt.io/qt/qt5.git qt6

cd qt6
git switch dev
perl init-repository --module-subset=qtbase,qtshadertools,qtdeclarative,qtcharts