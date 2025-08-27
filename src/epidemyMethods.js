import createModule from './wasm/epidemy.js';
import wasmUrl from './wasm/epidemy.wasm?url';

const Module = await createModule({
    locateFile: () =>  wasmUrl,
    print: (s) => (document.getElementById('out').textContent += s + '\n'),
    printErr: (s) => console.error(s),
});

var agentsRawArray;

// Wrap exported C functions
const create_simulator = Module.cwrap('create_simulator', null, ["number", "number", "number", "number", "number"]);
const add_random_agents = Module.cwrap('add_random_agents', null, ["number", "number", "number", "number"]);
const get_agents_raw_pointer = Module.cwrap('get_agents_raw', "number", []);

//export const getAgentX = Module.cwrap('getAgentX', "number", ["number"]);
//export const getAgentY = Module.cwrap('getAgentY', "number", ["number"]);
//export const getAgentSpeedX = Module.cwrap('getAgentSpeedX', "number", ["number"]);
//export const getAgentSpeedY = Module.cwrap('getAgentSpeedY', "number", ["number"]);
export const getNumberOfAgents = Module.cwrap('getNumberOfAgents', "number", []);
//export const getAgentState = Module.cwrap('getAgentState', "number", ["number"]);
const _step = Module.cwrap('step', null, ["number"]);

export function step(timeInSeconds) {
    _step(timeInSeconds);
    updateAgents();
}

export function updateAgents() {
    let count = getNumberOfAgents();
    let ptr = get_agents_raw_pointer();

    agentsRawArray = new Float64Array(Module.HEAPF64.buffer, ptr, count * 6);

    /*
    for (let index = 0; index < count; ++index) {
        let x = agentsRawArray[index * 6];
        let y = agentsRawArray[index * 6 + 1];
        let vx = agentsRawArray[index * 6 + 2];
        let vy = agentsRawArray[index * 6 + 3];
        let state = agentsRawArray[index * 6 + 4];
        let state_buff = agentsRawArray[index * 6 + 5];

        console.log(`{x: ${x}, y: ${y}, vx: ${vx}, vy: ${vy}, state: ${state}, state_buff: ${state_buff}}`);
    }
    */
}

export function getAgentX(index) {
    return agentsRawArray[index * 6]; // float64
}

export function getAgentY(index) {
    return agentsRawArray[index * 6 + 1]; // float64
}

export function getAgentSpeedX(index) {
    return agentsRawArray[index * 6 + 2]; // float64
}

export function getAgentSpeedY(index) {
    return agentsRawArray[index * 6 + 3]; // float64
}

export function getAgentState(index) {
    return agentsRawArray[index * 6 + 4]; // float64
}

export function createSimulator(DATA) {
    create_simulator(DATA.SPACE_WH, DATA.SPACE_WH, DATA.P_CONTAMINATION, DATA.CONTAMINATION_RADIUS, DATA.P_HEAL, DATA.P_DEATH, DATA.P_IMMUNE);
    updateAgents();
}

export function addRandomAgents(DATA) {
    add_random_agents(DATA.NUMBER_OF_AGENTS, DATA.AGENTS_SPEED_PER_SECONDS, DATA.NUMBER_OF_INFECTED, DATA.NUMBER_OF_IMMUNE);
    updateAgents();
}
