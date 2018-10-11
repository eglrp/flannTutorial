cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(planar_segmentation)

#find_package(PCL 1.2 REQUIRED)

#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

find_package(HDF5 REQUIRED)

include_directories(${HDF5_INCLUDE_DIR})

add_executable (flann_example flann_example.cpp)
target_link_libraries (flann_example ${HDF5_LIBRARIES} lz4)
