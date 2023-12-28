#! /bin/bash

for file in ../src/audioDatCopy/*
do  
    var=$(echo "$file" | cut -d/ -f4)
    echo $var
    mv $file ../out/data/$var
done

