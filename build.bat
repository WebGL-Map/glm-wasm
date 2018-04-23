@echo off

REM Make folders
if not exist "cmake-build-release" mkdir cmake-build-release
set glm-wasmSrc=%cd%
cd cmake-build-release

REM Get user input
if exist "emchainfile.txt" (
    set /p emscriptenToolChainFile=<emchainfile.txt
) else (
    set /p emscriptenToolChainFile="Enter full path to Emscripten ToolChain File: "
    echo %emscriptenToolChainFile% > emchainfile.txt
)

cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=%emscriptenToolChainFile%" -G "CodeBlocks - MinGW Makefiles" %glm-wasmSrc%
cd ..
cmake --build cmake-build-release --target index -- -j 4