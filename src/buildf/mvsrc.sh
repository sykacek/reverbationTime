#! /bin/bash

for file in ../audio_datcp/*
do  
    var=$(echo "$file" | cut -d/ -f4)
#    echo $var
    mv $file ../out/data/$var
done

