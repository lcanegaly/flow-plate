cmake_minimum_required(VERSION 3.0.0)
project(flowplate VERSION 0.1.1)


SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY(flowplate STATIC orificeflow.cpp)

