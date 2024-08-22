#! /bin/bash
if ! [[ -d build ]]; then
    mkdir build
fi

if ! [[ -d out ]]; then
    mkdir out
fi

if ! [[ -d src/audio_dat ]]; then
    mkdir src/audio_dat
fi

if ! [[ -d src/audio_datcp ]]; then
    mkdir src/audio_datcp
fi

if ! [[ -d src/temp ]]; then
    mkdir src/temp
fi

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

