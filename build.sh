#!/bin/bash

additionalCommand_Headers=1
additionalCommand_Doxygen=0
additionalCommand_Build=0

### additionalCommand_Headers
if [[ $additionalCommand_Headers == 1 ]]; then
    mkdir -p build/lib/include 
    rm -r build/lib/include/**
    cp include/*.h build/lib/include
    cp build/src/libUtils.a build/lib/libUtils.a
fi

### doxygen
if [[ $additionalCommand_Doxygen == 1 ]]; then
    cd docs
    doxygen Doxyfile
    cd ..
fi

### build
if [[ $additionalCommand_Build == 1 ]]; then
    # configure
    cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE=~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S. -Bbuild -G Ninja
    # build
    cmake --build build --config Debug --target app --
    # run
    cd build
    apps/app
    cd ../
fi