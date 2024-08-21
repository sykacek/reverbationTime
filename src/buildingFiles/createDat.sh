#! /bin/bash

rm -r ../src/audioDat
rm -r ../src/audioDatCopy


mkdir ../src/audioDat
mkdir ../src/audioDatCopy

for file in ../audioIn/*.wav
do
    var=$( echo "$file" |cut -d/ -f3 )
    sox $file ../src/audioDat/${var%.*}.dat
done