Requirements:
* node.js
* pixi.js version:>8.12.0
* emcc

Steps:
1. Compile the project to WebAssembly
```bash
emcc --no-entry core/agent.cpp core/epidemy.cpp core/virus_characteristics.cpp core/wasm.cpp  -o src/wasm/epidemy.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap","HEAPF64","HEAP32","HEAPU8"]'
```

2. Launch the server
```bash
npx vite
```