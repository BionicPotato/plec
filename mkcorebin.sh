#!/bin/sh

mkdir core.bin
cd core.bin
cmake ../core -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cd ..

