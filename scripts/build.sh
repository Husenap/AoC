#!/bin/bash

# touch the CMakeLists.txt file to force the GLOB to re-run.
touch CMakeLists.txt

# build the executables
cmake --build .build/