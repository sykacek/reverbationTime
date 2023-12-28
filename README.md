# reverbationTime
Small program for plotting and analyzing reverbation from .wav files
Program is running only on Linux, tested on Ubuntu 20. 04
# dependencies
Before building project you need to install dependencies
```sh
  sudo apt install sox gnuplot cmake
  ```

# build
For building project simply run 'run.sh' script in parental directory by running
```sh
  ./run.sh
  ```
# analyze and plot samples
Everytime you analyze audio first put audio samples in folder `audioIn`
and then in `build` folder run 
```sh
  make
  ```
Output files will be written into `out` folder, with gnuplot-generated graphs in `out/images`, processed raw files inside `out/data` folder
and statistical data in .txt file are written in `out/stats`.
Name of each output file is copied from input audio file, for better recognition. It is recommended not to use _ inside file names because of gnuplot. 
