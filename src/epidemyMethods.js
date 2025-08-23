import createModule from './wasm/epidemy.js';
import wasmUrl from './wasm/epidemy.wasm?url';

const Module = await createModule({
    locateFile: () =>  wasmUrl,
    print: (s) => (document.getElementById('out').textContent += s + '\n'),
    printErr: (s) => console.error(s),
});

// Wrap exported C functions
export const create_simulator = Module.cwrap('create_simulator', null, ["number", "number", "number", "number", "number"]);
export const add_random_agents = Module.cwrap('add_random_agents', null, ["number", "number", "number", "number"]);
export const getAgentX = Module.cwrap('getAgentX', "number", ["number"]);
export const getAgentY = Module.cwrap('getAgentY', "number", ["number"]);
export const getAgentSpeedX = Module.cwrap('getAgentSpeedX', "number", ["number"]);
export const getAgentSpeedY = Module.cwrap('getAgentSpeedY', "number", ["number"]);
export const getNumberOfAgents = Module.cwrap('getNumberOfAgents', "number", []);
export const getAgentState = Module.cwrap('getAgentState', "number", ["number"]);
export const step = Module.cwrap('step', null, ["number"]);