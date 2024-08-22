#! /bin/bash

# change this script if you would like to use different utility

for file in `ls input/*.wav`
do
    var=$( echo "$file" |cut -d/ -f2 )
    sox $file src/audio_dat/${var%.*}.dat
done