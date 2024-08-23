## UNIT TESTING

Functions used in C++ engine are unit tested using [Google Tests](https://github.com/google/googletest). Below are the results of the tests, if you desire to perform tests yourself you can do it simply by running the `test.sh` scripit in the root of directory. Building Google Tests manually using CMake is also possible.

### AUTOMATED BUILD
Build procces of tests is automated using via `test.sh` script in root directory of the project. To build the tests this way execute the script in project root directory.
```sh
    cd /path-to-repository/
    ./test.sh
```
Execute privileges are automaticly obtained by running `build.sh` script, if you did not run `build.sh` script, get privileges manually
```sh
    chmod u+x test.sh
```
Script will create CMake environment for you and run executables.

### MANUAL BUILD
Building with CMake manually is also possible. In `test/` directory prepare CMake environment and run CMake
```sh
    cd /path-to-repository/test/
    mkdir build
    cd build
    cmake ..
    make
    ./tests_exe
```