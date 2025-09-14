#!/bin/bash

if [ "$1" = "-r" ]; then
    build_type="Release"
    build_dir="build-release"
else
    build_type="Debug"
    build_dir="build-debug"
fi

mkdir -p "$build_dir"
cd "$build_dir"
cmake -DCMAKE_BUILD_TYPE="$build_type" ..
cmake --build .
