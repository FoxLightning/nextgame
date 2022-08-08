mkdir .\build;
cd .\build;
conan install .. --build=missing;
cd ..;
cmake -S ./ -B ./build -G "Visual Studio 16 2019";
cd build;
cmake --build . --config Release;
cd ..;

