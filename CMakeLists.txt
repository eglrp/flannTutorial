cmake_minimum_required(VERSION 2.8)

project(flannTutorial)

#set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_C_COMPILER /usr/bin/gcc-6)
#set (CMAKE_CXX_COMPILER /usr/bin/g++-6)


#find_package(glfw3 REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

#include_directories(/home/yousof/robotics/flann/src/cpp/flann)
#link_directories(/home/yousof/robotics/flann/build/lib)

#find_library(flann_cpp
#		name libflann_cpp_s.a
#		PATHS /home/yousof/robotics/flann/build/lib/
#		NO_DEFAULT_PATH NO_CMAKE_SYSTEM_PATH)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


#set(HDF5_CXX mpiCC)
#set(HDF5_CLINKER mpiCC)
#find_package(HDF5 REQUIRED)
#include_directories(${HDF5_INCLUDE_DIR})

#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})

add_executable(${PROJECT_NAME}
    main.cpp)

target_link_libraries(${PROJECT_NAME}
#    glfw
     ${HDF5_LIBRARIES}
     ${PCL_LIBRARIES}
#    lz4
    ) #glew32f

#target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
#target_link_libraries(
#	${PROJECT_NAME} 
#	${HDF5_LIBRARIES} 
#	) #flann_cpp ${OPENGL_gl_LIBRARY}

#set(FLANN_LIBRARY /home/yousof/robotics/flann/build/lib/libflann_cpp_s.a)
#set(FLANN_LIBRARY_DEBUG /home/yousof/robotics/flann/build/lib/libflann_cpp_s.a)
#set(FLANN_INCLUDE_DIRS /home/yousof/robotics/flann/src/cpp/flann)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

#message("CMAKE_MODULE_PATH=== ${CMAKE_MODULE_PATH}")
