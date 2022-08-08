#!/bin/bash
mkdir ./build
cd ./build
conan install .. --build=missing;
cd ..;
cmake -S ./ -B ./build -G "Unix Makefiles";
cd build;
cmake --build . --config Release;
cd ..;
