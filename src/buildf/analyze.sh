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

# create audio samples
source src/buildf/dat_create.sh

# proccess data with apx_coeff = 600
./build/REV 600

# move files to to output directory 
for file in src/audio_datcp/*
do
    var=$(echo $file | cut -d/ -f3)
    cp $file output/data/$var
done

# plot data using gnuplot 
./src/buildf/gnuplot.sh

# rename .png files
for file in output/images/*.dat.png
do
    var=${file%.*}
    mv $file ${var%.*}
done

# create additional statistical data
./build/STATS