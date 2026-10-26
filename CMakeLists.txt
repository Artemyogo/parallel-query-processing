cmake_minimum_required(VERSION 3.16)
project(PW LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test src/test.cpp src/gen.cpp src/slow.cpp src/fast_openmp.cpp src/fast_thread.cpp)
target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(OpenMP REQUIRED)
target_link_libraries(test PRIVATE OpenMP::OpenMP_CXX)
