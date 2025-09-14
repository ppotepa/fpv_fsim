#!/bin/bash

if [ "$1" = "-r" ]; then
    build_dir="build-release"
    exe_path="$build_dir/Release/fpv_fsim"
else
    build_dir="build-debug"
    exe_path="$build_dir/Debug/fpv_fsim"
fi

if [ -f "$exe_path" ]; then
    "$exe_path"
else
    echo "Executable not found. Please build first."
fi
