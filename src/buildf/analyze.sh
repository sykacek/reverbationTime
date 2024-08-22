#! /bin/bash

#run this script to analyze audio samples

source /src/buildf/dat_create.sh
./build/REV
source /src/buildf/mvsrc.sh
./src/buildf/gnuplot.sh
./src/buildf/rename.sh
./build/STATS