cmake_minimum_required(VERSION 2.8)

project(flannTutorial)

set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_C_COMPILER /usr/bin/gcc-6)
#set (CMAKE_CXX_COMPILER /usr/bin/g++-6)

#find_package(PCL REQUIRED)

#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

find_package(OpenGL REQUIRED)
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

find_package(Eigen3 REQUIRED)

# icnlude Pangolin
include_directories("${CMAKE_SOURCE_DIR}/../Pangolin/include" "${CMAKE_SOURCE_DIR}/../Pangolin/build/src/include")
link_directories("${CMAKE_SOURCE_DIR}/../Pangolin/build/src")


add_executable(${PROJECT_NAME}
    main.cpp)

target_link_libraries(${PROJECT_NAME}
     ${HDF5_LIBRARIES}
#     ${PCL_LIBRARIES}
     lz4
     pangolin
     Eigen3::Eigen
     ${OPENGL_LIBRARIES}
     )

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#  message(STATUS "dir='${dir}'")
#endforeach()

#message("CMAKE_MODULE_PATH=== ${CMAKE_MODULE_PATH}")
