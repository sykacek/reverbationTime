#! /bin/bash

# run this script to analyze audio samples

# check if there are even audio samples
if [[ `ls input/*` == "" ]]; then
    echo "Error: no .wav file"
    echo "Please insert any and try again"
    exit 1
fi

# reset cache files
if [[ -d src/audio_dat ]]
then
    rm -r src/audio_dat
fi

mkdir src/audio_dat

if [[ -d src/audio_datcp ]]
then
    rm -r src/audio_datcp
fi

mkdir src/audio_datcp

#stage 1 - create audio samples
source src/buildf/dat_create.sh

./build/REV

# move files to to out directory 
for file in src/audio_datcp
do
    var=$(echo $file | cut -d/ -f3)
    echo $var
    cp $file out/data/$var
done

# source src/buildf/mvsrc.sh
./src/buildf/gnuplot.sh

#rename .png files
for file in output/images/*.dat.png
do
    var=${file%.*}
    mv $file ${var%.*}
done
./src/buildf/rename.sh

./build/STATS