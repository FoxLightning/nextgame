project(nextgame)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# include header files
include_directories(source/public)
# parse source files
file(GLOB SOURCES source/private/*.cpp)

# add executable files
add_executable(nextgame ${SOURCES} source/nextgame.cpp)
# link libs from conan
target_link_libraries(nextgame ${CONAN_LIBS})
