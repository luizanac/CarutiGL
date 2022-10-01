cmake_minimum_required(VERSION 3.21)
project(CarutiGL)

set(CMAKE_CXX_STANDARD 20)

##Find packages
find_package(OpenGL REQUIRED)

#Configure exec

file(GLOB SOURCES **/*.cpp
        src/**/*.cpp
        src/Core/Graphics/*.cpp
        src/Core/Input/*.cpp
        third/glad/src/glad.c
        third/stb/src/stb_image.cpp)
add_executable(CarutiGL ${SOURCES} ${RES_FILES})

#Copy resources
add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources
        ${CMAKE_CURRENT_BINARY_DIR}/Resources)
add_dependencies(CarutiGL copy_resources)

#Include directories
target_include_directories(CarutiGL PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/fmt/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/stb/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/glm/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/perlin
        )

#Link libraries
target_link_libraries(CarutiGL
        ${CMAKE_SOURCE_DIR}/third/glfw/lib/libglfw3.a
        ${CMAKE_SOURCE_DIR}/third/fmt/lib/libfmtd.a
        )


