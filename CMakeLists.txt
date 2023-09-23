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

add_executable(busca1 BuscaIrrevogavel.cpp)
target_link_libraries(busca1 casal)

add_executable(busca2 BuscaBacktracking.cpp)
target_link_libraries(busca2 casal)

add_executable(busca3 BuscaLargura.cpp)
target_link_libraries(busca3 casal)
