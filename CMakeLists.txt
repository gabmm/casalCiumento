cmake_minimum_required(VERSION 3.10.2)
project(casalCiumento)

set(CMAKE_CXX_STANDARD 17)

# Build the library
include_directories(include)
file(GLOB source_files src/*.cc)
add_library(casal ${source_files})
target_include_directories(casal PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(casalCiumento main.cpp)
target_link_libraries(casalCiumento casal)

add_executable(manual manual.cpp)
target_link_libraries(manual casal)

