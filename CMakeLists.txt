project(nextgame)
cmake_minimum_required(VERSION 3.23.2)
# enable std::format
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")

# setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# set some variables
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# include header files
include_directories(source/public)
# parse source files
file(GLOB SOURCES source/private/*.cpp)
file(GLOB HEADERS source/public/*.hpp)

# add executable files
add_executable(nextgame ${HEADERS} ${SOURCES} source/nextgame.cpp)
# link libs from conan
target_link_libraries(nextgame ${CONAN_LIBS})
# copy content
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/content DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
