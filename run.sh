#!/bin/bash
cd build || { echo "Build directory not found!"; exit 1; }
cmake .. || { echo "CMake failed!"; exit 1; }
make || { echo "Make failed!"; exit 1; }
export QT_QPA_PLATFORM=xcb
./grandmaster || { echo "Execution of grandmaster failed!"; exit 1; }