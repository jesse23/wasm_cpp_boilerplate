/**
 * WASM main entry
 */

// references:
// - https://medium.com/@robaboukhalil/hit-the-ground-running-with-webassembly-56cf9b2fa35d
// - https://hub.docker.com/r/trzeci/emscripten/

// build:
// - emcc src/*.cxx src/vmo/*.cxx -o public/example.js -I./src -s EXPORTED_FUNCTIONS="['_squareVal', '_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"
// - g++  src/*.cxx src/vmo/*.cxx -o public/example -I./src

// test:
// - npm start -> launch test page
// - node ./dist/index.js -> nodeJS
// - ./example -> c++ main

#include <utils/utils.hxx>

#ifndef EMSCRIPTEN
#include <iostream>
#else
#include <emscripten.h>
#endif

int main()
{
#ifndef EMSCRIPTEN
    float x = 12.5;
    std::cout << "Computing: " << x << " * " << x << " = " << squareVal(x) << std::endl;
#else
    EM_ASM({
        squareVal = Module.cwrap('squareVal', 'number', ['number']);
        var x = 12.5;
        console.log('Computing: ' + x + ' * ' + x + ' = ' + squareVal(x));
    });
#endif
}