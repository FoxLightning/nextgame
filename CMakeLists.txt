project(nextgame)
cmake_minimum_required(VERSION 2.8.12)

# setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# set some variables
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# include header files
include_directories(source/public)
# parse source files
file(GLOB SOURCES source/private/*.cpp)
file(GLOB HEADERS source/public/*.h)

# add executable files
add_executable(nextgame ${HEADERS} ${SOURCES} source/nextgame.cpp)
# link libs from conan
target_link_libraries(nextgame ${CONAN_LIBS})
# copy content
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/content DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
