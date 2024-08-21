#! /bin/bash
if ! [[ -e audioIn/*.wav ]]; then
    echo "Error: no .wav file"
    echo "Please insert any and try again"
    exit 1
fi


if ! [[ -r *.wav ]]; then
    echo "File is not readable!"
    exit 1
fi

rm -r ../src/audioDat
rm -r ../src/audioDatCopy


mkdir ../src/audioDat
mkdir ../src/audioDatCopy

for file in ../audioIn/*.wav
do
    var=$( echo "$file" |cut -d/ -f3 )
    sox $file ../src/audioDat/${var%.*}.dat
done