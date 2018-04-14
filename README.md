# Glm-wasm [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

The primary repository for client side map rendering. This code can be written in any language but must be compiled to 
WebAssembly.

## Prerequisites
**Note:** In order to build this project you will need the following installed. Some applications might also need to be 
on the system path.
* [MinGW](http://www.mingw.org/)
* [CMake](https://cmake.org/)
* [Emscripten](https://kripken.github.io/emscripten-site/index.html)

## Building
When building this project make sure to set the `-DCMAKE_TOOLCHAIN_FILE` CMake option to the `Emscripten.cmake` 
toolchain file.

## Deploying
From: [http://emscripten.org](http://emscripten.org)

To serve wasm in the most efficient way over the network, make sure your web server has the proper MIME time for `.wasm`
files, which is application/wasm. That will allow streaming compilation, where the browser can start to compile code 
as it downloads.

In Apache, you can do this with:
```
AddType application/wasm .wasm
```

Also make sure that gzip is enabled:
```
AddOutputFilterByType DEFLATE application/wasm
```