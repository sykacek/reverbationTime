# Reverbation Time
Small program for plotting and analyzing reverbation from .wav files
Program is running only on Linux, tested on Ubuntu 20. 04

### dependencies
Before building project you need to install dependencies
```sh
  sudo apt install sox gnuplot cmake make build-essential
  ```

### build
You may fisrt need to give `run.sh` in parental directory execute permission 
```sh
  chmod u+x run.sh
```
after run `run.sh` script by running
```sh
  ./run.sh
  ```
This will create needed scripts and executables inside `build/` directory
### analyze and plot samples
Everytime you analyze audio, first put audio samples in directory `audioIn/`
and then in `build/` directory run 
```sh
  make
  ```
Output files will be written into `out/` directory, with gnuplot-generated graphs in `out/images/`, processed raw files inside `out/data/` directory
and statistical data in .txt file are written in `out/stats/`. Output files ARE NOT cleared before NEW RUN automatically, you have to clear them manually. 
Name of each output file is copied from input audio file, for better recognition. It is recommended not to use '_' inside file names because of gnuplot. 
Data in `out/data/` files are starting from highest bit in whole audio file and from this place program is computing reverbation time. In `out/stats/` files are printed values decreased by 10 dB, and highest
measured decrease, if decrease of 60dB was not measured there is artihmetical avarge of values measured with 10dB steps and maximum decrease.
