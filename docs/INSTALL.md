### INSTALLATION GUIDE 
This document describes how to install and run the project for computing reverabtion time. 
Think of this project as collection of tools more than single executable program. Although C++ files are build using CMake it is recommended to follow the guide below. Building with CMake manually won't prepare workspace completely (additional bash scripts won't be copied etc.)

First, install dependencies
```sh
  sudo apt install sox gnuplot cmake make build-essential
```

Then clone the repository

```sh
    git clone https://github.com/sykacek/reverbationTime.git
    cd reverbationTime
```
then execute
```sh
    ./run.sh
```
make sure you have right privileges, to obtain executable privilege execute
```sh
    chmod u+x run.sh
```
which will run installation script. This will prepare workspace for further usage.

### FIRST RUN
Put desired audio samples into the folder `audioIn` in your base directory. Only .wav files are supported, other files in the directory will be ignored.
```sh
    cp /path-to-audio/audio.wav /path-po-repository/audioIn/
```

and then in `build` directory execute `make`
```sh
    cd build
    make
``````sh
  sudo apt install sox gnuplot cmake make build-essential
  ```
