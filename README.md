Requirements:
* node.js
* pixi.js version:>8.12.0
* emcc

Steps:
1. Compile the project to WebAssembly
```bash
emcc --no-entry core/agent.cpp core/vector2d.cpp core/epidemy.cpp core/wasm.cpp  -o public/epidemy.js -s MODULARIZE=1 -s EXPORT_ES6=1 -s EXPORTED_RUNTIME_METHODS='["cwrap"]'
```

2. Launch the server
```bash
node server.js
```