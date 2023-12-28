#! /bin/bash

mkdir build out out/data out/images out/stats src/temp src/audioDatCopy
cmake -S . -B build
cmake -DCMAKE_BUILD_TYPE=Release build
cmake --build build
cp src/buildingFiles/* build/

for file in build/*.sh
do
	chmod u+x $file
done
