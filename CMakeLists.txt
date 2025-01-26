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

# Add a custom command that will depend on changes in the res folder
file(GLOB_RECURSE RESOURCES "${CMAKE_SOURCE_DIR}/res/*")

# Ensure to copy the resources and update the build directory, removing stale files
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/res  # Remove existing files in the build res folder
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res  # Copy the updated resources
        COMMENT "Copying resource files to the build directory and removing outdated files"
)

target_link_libraries(GraphicsProgramming PRIVATE glfw3 opengl32 glew32)
add_dependencies(GraphicsProgramming copy_resources)

