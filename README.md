Requirements:
* node.js
* pixi.js version:>8.12.0
* emcc

Steps:
1. Compile the project to WebAssembly
```bash
emcc agent.cpp epidemy.cpp main.cpp vector2d.cpp epidemy.wasm
```

2. Launch the server
```bash
node server.js
```