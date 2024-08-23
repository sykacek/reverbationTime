#! /bin/bash

if [[ -d output ]]
then
    rm -r output
fi

mkdir -p output/data
mkdir output/images
mkdir output/stats