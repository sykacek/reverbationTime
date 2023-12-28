#! /bin/bash

mkdir build
cmake -S . -B build
cmake build
cmake --build build
cp src/buildingFiles/* build/