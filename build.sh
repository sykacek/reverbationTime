#! /bin/bash
rm -r build out src/audioDat src/temp src/audioDatCopy || true

mkdir build out out/data out/images out/stats src/temp src/audioDat src/audioDatCopy || true
cmake -S . -B build

#uncomment to compile Release executable
#cmake -DCMAKE_BUILD_TYPE=Release build

cmake --build build
make -C build

for file in `ls src/buildf/*.sh`
do
    chmod u+x $file
done

cp src/buildf/analyze.sh . 
chmod u+x analyze.sh

