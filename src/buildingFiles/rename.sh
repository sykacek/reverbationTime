#! /bin/bash

for file in ../out/images/*.dat.png
do  
    var=${file%.*}
#    echo ${var%.*}.png
    mv $file ${var%.*}.png
done