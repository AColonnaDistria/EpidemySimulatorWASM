Requirements:
* node.js
* pixi.js version:>8.12.0
* emcc
* vite.js

Steps for local deployment:
1. Compile the project to WebAssembly
First load the environment variables of emscripten:
```bash
source ~/emsdk/emsdk_env.sh
```

then compile the project

```bash
emcc --no-entry -O3 core/*.cpp -o src/wasm/epidemy.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap","HEAPF64","HEAP32","HEAPU8"]'
```

2. Launch the server with vite.js
```bash
npx vite
```

and open in the browser 

Remarks:
If you need a lot of agents, you can increase the memory size (eg 128MB) available
```bash
emcc --no-entry -O3 core/*.cpp -o src/wasm/epidemy.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap","HEAPF64","HEAP32","HEAPU8"] -s INITIAL_MEMORY=128MB'
```

or make it expand at runtime
```bash
emcc --no-entry -O3 core/*.cpp -o src/wasm/epidemy.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap","HEAPF64","HEAP32","HEAPU8"] -s ALLOW_MEMORY_GROWTH=1'
```