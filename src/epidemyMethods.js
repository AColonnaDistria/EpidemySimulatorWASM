import createModule from './wasm/epidemy.js';
import wasmUrl from './wasm/epidemy.wasm?url';

const Module = await createModule({
    locateFile: () =>  wasmUrl,
    print: (s) => (document.getElementById('out').textContent += s + '\n'),
    printErr: (s) => console.error(s),
});

export function createSimulator(DATA) {
    create_simulator(DATA.SPACE_WH, DATA.SPACE_WH, DATA.P_CONTAMINATION, DATA.CONTAMINATION_RADIUS, DATA.P_HEAL, DATA.P_DEATH, DATA.P_IMMUNE);
}

export function addRandomAgents(DATA) {
    add_random_agents(DATA.NUMBER_OF_AGENTS, DATA.AGENTS_SPEED_PER_SECONDS, DATA.NUMBER_OF_INFECTED, DATA.NUMBER_OF_IMMUNE);
}

// Wrap exported C functions
const create_simulator = Module.cwrap('create_simulator', null, ["number", "number", "number", "number", "number"]);
const add_random_agents = Module.cwrap('add_random_agents', null, ["number", "number", "number", "number"]);
export const getAgentX = Module.cwrap('getAgentX', "number", ["number"]);
export const getAgentY = Module.cwrap('getAgentY', "number", ["number"]);
export const getAgentSpeedX = Module.cwrap('getAgentSpeedX', "number", ["number"]);
export const getAgentSpeedY = Module.cwrap('getAgentSpeedY', "number", ["number"]);
export const getNumberOfAgents = Module.cwrap('getNumberOfAgents', "number", []);
export const getAgentState = Module.cwrap('getAgentState', "number", ["number"]);
export const step = Module.cwrap('step', null, ["number"]);