## UNIT TESTING

Functions used in C++ engine are unit tested using [Google Tests](https://github.com/google/googletest). Below are the results of the tests, if you desire to perform tests yourself you can do it by building Google Tests manually using CMake.

### Manual build
Manual build is nothing more than usual CMake project build. In `test/` directory prepare CMake environment and run CMake
```sh
    cd /path-to-repository/test/
    mkdir build
    cd build
    cmake ..
    make
    ./tests_exe
```

## Tests and results
Tests were aimed to various aspects of functions, trying to reach maximum level of randomization. For text file proccessing functions main goal was to test formating of generated files (lines and columns, etc.) and contents of generated files. Comparing files was realized using `cmp` shell command. When testing one directional functions (from the program to the file and backwards) there is not possibility how to compare data in the program with data in the file. Only way to tests those functions is using *reference (match) files*. *Reference file* is a file, which contents are known beforehand, and program is made to produce same contents. Afterwards, comparing with reference file is possible.

#### Tests naming conventions
* Each test suit is named after the functions which is tested.
* Capital letters are substituted with underscore + letter, eg. function fooBar will be foo_bar
* Test names should be intuitive