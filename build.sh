#!/bin/bash

additionalPack_CMake=0
additionalPack_Conan=0
additionalPack_Doxygen=1

# conan
if [[ $additionalPack_Conan == 1 ]]; then
    conan install .. --build=missing
fi

# CMake 
if [[ $additionalPack_CMake == 1 ]]; then
    rm -rf build
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=DEBUG
    cmake --build .
    ./apps/app
    cd ..
fi

# doxygen
if [[ $additionalPack_Doxygen == 1 ]]; then
    cd docs
    doxygen Doxyfile
    cd ..
fi

echo "finished"
