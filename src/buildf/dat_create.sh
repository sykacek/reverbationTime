#! /bin/bash
if ! [[ -e ../../audioIn/*.wav ]]; then
    echo "Error: no .wav file"
    echo "Please insert any and try again"
    exit 1
fi


if ! [[ -r ../../audioIn/*.wav ]]; then
    echo "File is not readable!"
    exit 1
fi

rm -r ../audioDat 
rm -r ../audioDatCopy


mkdir ../audioDat
mkdir ../audioDatCopy

for file in ../../audioIn/*.wav
do
    var=$( echo "$file" |cut -d/ -f4 )
    echo $var
    sox $file ../audioDat/${var%.*}.dat
done