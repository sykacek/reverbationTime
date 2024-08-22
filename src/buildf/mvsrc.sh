#! /bin/bash

for file in ../audioDatCopy/*
do  
    var=$(echo "$file" | cut -d/ -f4)
#    echo $var
    mv $file ../out/data/$var
done

