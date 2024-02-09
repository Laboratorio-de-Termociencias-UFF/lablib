cmake_minimum_required(VERSION 3.24.0)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(CUDA)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_ARCHITECTURES 61 86)

project(test VERSION 0.1)

find_package(CUDAToolkit)

# Add Libraries
add_subdirectory(src/structure)
add_subdirectory(src/error)

# Add executables
add_executable(${PROJECT_NAME} main.c)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)

target_link_libraries(${PROJECT_NAME} PUBLIC Structure Error)