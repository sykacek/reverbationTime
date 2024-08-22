#! /bin/bash
if ! [[ -e audioIn/*.wav ]]; then
    echo "Error: no .wav file"
    echo "Please insert any and try again"
    exit 1
fi


if ! [[ -r audioIn/*.wav ]]; then
    echo "File is not readable!"
    exit 1
fi

rm -r ../audio_dat 
rm -r ../audio_datcp


mkdir ../audio_dat
mkdir ../audio_datcp

for file in ../../audioIn/*.wav
do
    var=$( echo "$file" |cut -d/ -f4 )
    echo $var
    sox $file ../audio_dat/${var%.*}.dat
done