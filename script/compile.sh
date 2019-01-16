#!/bin/bash

# compile all test cpp files for testing!

cd ..

mkdir -p build
cd build
cmake ..
make -j4

cd ../script