cmake_minimum_required(VERSION 3.9)
project(glm_wasm)
add_subdirectory(glm)

set(CMAKE_CXX_STANDARD 11)

include_directories(/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

link_libraries(glm)

set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(EMCC_LINKER_FLAGS_GLOBAL "-s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall']\"")
set(CMAKE_CXX_FLAGS_DEBUG  "${EMCC_LINKER_FLAGS_GLOBAL}")
set(CMAKE_CXX_FLAGS_RELEASE " -O3 ${EMCC_LINKER_FLAGS_GLOBAL}")
add_executable(index ${HEADERS} ${SOURCES})