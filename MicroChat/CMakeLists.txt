cmake_minimum_required(VERSION 3.5)
project(microchat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_INSTALL_PREFIX /usr/local/bin)

find_package(libmongoc-1.0 REQUIRED)
add_subdirectory(src)