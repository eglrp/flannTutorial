cmake_minimum_required(VERSION 2.8)

project(flannTutorial)

set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_C_COMPILER /usr/bin/gcc-6)
#set (CMAKE_CXX_COMPILER /usr/bin/g++-6)

find_package(HDF5)
find_package(PCL 1.2 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


include_directories(${PCL_INCLUDE_DIRS}
    ${HDF5_INCLUDE_DIR})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

add_executable(${PROJECT_NAME}
    main.cpp
    visuallizer.hpp)


target_link_libraries(${PROJECT_NAME}
    glfw
    ${PCL_LIBRARIES}
    lz4) #glew32f

#target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${HDF5_LIBRARIES})
