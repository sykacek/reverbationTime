#! /bin/bash

mkdir build
cmake -S . -B build
cmake build
cmake --build build
cp src/buildingFiles/* build/

for file in build/*.sh
do
  chmod u+x $file
done
