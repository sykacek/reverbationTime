#! /bin/bash
if ! [[ -d build ]]; then
    mkdir build
fi

if ! [[ -d output/data ]]; then
    mkdir -p output/data
fi

if ! [[ -d output/images ]]; then
    mkdir -p output/images
fi

if ! [[ -d output/stats ]]; then
    mkdir -p output/stats
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
#cmake -DCMAKE_BUILD_TYPE=Release --build build

cmake --build build
make -C build

for file in `ls src/buildf/*.sh`
do
    chmod u+x $file
done

chmod u+x analyze.sh 
chmod u+x clear.sh
chmod u+x test.sh