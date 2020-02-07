#!/bin/sh

mkdir -p build
set(CMAKE_BUILD_FILES_DIRECTORY build\)
set(CMAKE_BUILD_DIRECTORY build\)

cmake . 
