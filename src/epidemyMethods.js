import createModule from './wasm/epidemy.js';
import wasmUrl from './wasm/epidemy.wasm?url';

const Module = await createModule({
    locateFile: () =>  wasmUrl,
    print: (s) => console.log(s),
    printErr: (s) => console.error(s),
});

var agentsRawArray;
var statsRawArray;

// Wrap exported C functions
const create_simulator = Module.cwrap('create_simulator', null, ["number", "number", "number", "number", "number"]);
const add_random_agents = Module.cwrap('add_random_agents', null, ["number", "number", "number", "number"]);
const get_agents_raw_pointer = Module.cwrap('get_agents_raw', "number", []);
const get_epidemy_stats_raw_pointer = Module.cwrap('getStatsPtr', "number", []);
const set_virus_characteristics = Module.cwrap('set_virus_characteristics', null, ["number", "number", "number", "number", "number"])
export const getNumberOfAgents = Module.cwrap('getNumberOfAgents', "number", []);
const _step = Module.cwrap('step', null, ["number"]);

export function step(timeInSeconds) {
    _step(timeInSeconds);
    updateAgents();
}

export function updateAgents() {
    let count = getNumberOfAgents();
    let agents_ptr = get_agents_raw_pointer();
    let stats_ptr = get_epidemy_stats_raw_pointer();

    agentsRawArray = new Float64Array(Module.HEAPF64.buffer, agents_ptr, count * 6);
    statsRawArray = new Int32Array(Module.HEAP32.buffer, stats_ptr, 4);
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

export function getNumberOfHealthy(index) {
    return statsRawArray[0]; // int32
}

export function getNumberOfInfected(index) {
    return statsRawArray[1]; // int32
}

export function getNumberOfImmune(index) {
    return statsRawArray[2]; // int32
}

export function getNumberOfDead(index) {
    return statsRawArray[3]; // int32
}

export function createSimulator(DATA) {
    create_simulator(DATA.SPACE_WH, DATA.SPACE_WH, DATA.P_CONTAMINATION, DATA.CONTAMINATION_RADIUS, DATA.P_HEAL, DATA.P_DEATH, DATA.P_IMMUNE);
    updateAgents();
}

export function addRandomAgents(DATA) {
    add_random_agents(DATA.NUMBER_OF_AGENTS, DATA.AGENTS_SPEED_PER_SECONDS, DATA.NUMBER_OF_INFECTED, DATA.NUMBER_OF_IMMUNE);
    updateAgents();
}

export function setVirusCharacteristics(DATA) {
    set_virus_characteristics(DATA.P_CONTAMINATION, DATA.CONTAMINATION_RADIUS, DATA.P_HEAL, DATA.P_DEATH, DATA.P_IMMUNE);
}