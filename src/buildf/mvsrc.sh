#! /bin/bash

for file in src/audio_datcp/*
do  
    var=$(echo "$file" | cut -d/ -f3)
#    echo $var
    mv $file output/data/$var
done

