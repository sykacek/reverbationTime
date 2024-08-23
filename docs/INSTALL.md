## INSTALLATION GUIDE 
This document describes how to install and run the project for analyzing reverabtion. 
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
    ./build.sh
```
make sure you have right privileges, to obtain executable privilege execute
```sh
    chmod u+x build.sh
```
which will run installation script. This will prepare workspace for further usage.

### PROJECT TREE

Running build script will prepare workspace as shown below
``` sh
reverbationTime
│
├── build - CMake build files are located here
├── docs - documentation
├── input - put audio samples here
├── output
│   ├── data - raw .dat output data
│   ├── images - gnuplot generated plots 
│   └── stats - statistical data from measurement
├── src - sprogram files
└── test - unit tests
```

### ANALYZE AUDIO SAMPLES
Put desired audio samples into the `input` directory. Only .wav files are supported, other files in the directory will be ignored.
```sh
    cp /path-to-audio/audio.wav /path-po-repository/input/
```

and then in the root directory of the project execute `./analyze.sh`
```sh
    # if you are not in root directory already
    cd /path-to-repository/
    ./analyze.sh
```
