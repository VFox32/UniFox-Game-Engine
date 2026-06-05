#!/usr/bin/env bash

set -e

BUILD_TYPE=${1:-Release}
BUILD_DIR="build/$BUILD_TYPE"

echo "Configuring ($BUILD_TYPE) into $BUILD_DIR..."
cmake -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE

echo "Building..."
cmake --build "$BUILD_DIR"

echo "Build Complete"