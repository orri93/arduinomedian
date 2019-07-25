cmake_minimum_required(VERSION 3.1...3.15)

project(ArduinoMedianLib VERSION 1.0
  DESCRIPTION "FDS Arduino libraries Google unit tests"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

add_library(ArduinoMedianLib fdsmedian.cpp fdsmedian.h)
