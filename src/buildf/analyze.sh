#! /bin/bash

#run this script to analyze audio samples

./src/buildf/dat_create.sh
./build/REV
./src/buildf/mvsrc.sh
./src/buildf/gnuplot.sh
./src/buildf/rename.sh
./build/STATS