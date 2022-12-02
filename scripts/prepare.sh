#!/bin/bash

# make sure directories exists
mkdir -p cmake
mkdir -p src
mkdir -p input

# Add executable to CMakeLists.txt
cat <<EOT > cmake/day_$1.cmake
add_executable(day_$1 src/day_$1.cpp)
add_test(NAME day_$1 COMMAND day_$1 WORKING_DIRECTORY \${CMAKE_SOURCE_DIR}/input)
EOT


# Add source file to src dir
cat <<EOT > src/day_$1.cpp
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_$1");

  cout << "answer" << endl;

  return 1;
}
EOT


# Prepare input file
touch input/day_$1
