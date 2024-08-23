#! /bin/bash

# perform unit tests

if ! [[ -d test/build ]]
then
    mkdir test/build
fi

cmake -S test -B test/build
make -C test/build

./test/build/tests_exe