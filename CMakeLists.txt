cmake_minimum_required(VERSION 3.25)
project(AoC)

enable_testing()

# Glob cmake files for days in cmake/ directory and include them
file(GLOB cmake_days ${CMAKE_CURRENT_SOURCE_DIR}/cmake/[^_]*.cmake)

foreach(day ${cmake_days})
  include(${day})
endforeach()
