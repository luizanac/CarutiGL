cmake_minimum_required(VERSION 3.23)
project(CarutiGL)

set(CMAKE_CXX_STANDARD 17)

##Find packages
find_package(OpenGL REQUIRED)

#Configure exec

file(GLOB SOURCES **/*.cpp third/glad/src/glad.c)
add_executable(CarutiGL ${SOURCES} ${RES_FILES})

#Copy shaders
add_custom_target(copy_shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Resources/Shaders
        ${CMAKE_CURRENT_BINARY_DIR}/Resources/Shaders)
add_dependencies(CarutiGL copy_shaders)

#Include directories
target_include_directories(CarutiGL PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third/glad/include)

#Link libraries
IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows

    target_link_libraries(CarutiGL ${CMAKE_SOURCE_DIR}/third/glfw/lib/libglfw3.a)

ENDIF ()


