cmake_minimum_required(VERSION 3.27)
project(GraphicsProgramming)

set(CMAKE_CXX_STANDARD 17)

# Add GLFW include headers and library directories
include_directories(${CMAKE_SOURCE_DIR}/libs/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glew/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glm)

link_directories(${CMAKE_SOURCE_DIR}/libs/glfw/lib)
link_directories(${CMAKE_SOURCE_DIR}/libs/glew/lib)

set(HEADER_FILES
        ${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
)
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/c_files/SOIL2.c
        ${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/c_files/image_DXT.c
        ${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/c_files/image_helper.c
        ${CMAKE_SOURCE_DIR}/third_party/SOIL2_1.31/c_files/wfETC.c
)
add_executable(GraphicsProgramming ${HEADER_FILES} ${SOURCE_FILES})

# Create a custom target that always runs so that resources are always updated on running
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
        COMMENT "Copying resource files to the build directory"
)

target_link_libraries(GraphicsProgramming PRIVATE glfw3 opengl32 glew32)

add_dependencies(GraphicsProgramming copy_resources)

