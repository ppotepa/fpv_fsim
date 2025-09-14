#!/bin/bash

if [ "$1" = "-r" ]; then
    build_dir="build-release"
else
    build_dir="build-debug"
fi

if [ -f "$build_dir/fpv_fsim" ]; then
    cd "$build_dir"
    ./fpv_fsim
else
    echo "Executable not found. Please build first."
fi
