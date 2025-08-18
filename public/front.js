import createModule from './epidemy.js';

const Module = await createModule({
    locateFile: (p) => p, // ensures it finds epidemy.wasm next to epidemy.js
    print: (s) => (document.getElementById('out').textContent += s + '\n'),
    printErr: (s) => console.error(s),
});

// Wrap exported C functions
const create_simulator = Module.cwrap('create_simulator', null, ["number", "number"]);
const add_random_agents = Module.cwrap('add_random_agents', null, ["number", "number"]);
const getAgentX = Module.cwrap('getAgentX', "number", ["number"]);
const getAgentY = Module.cwrap('getAgentY', "number", ["number"]);
const getAgentSpeedX = Module.cwrap('getAgentSpeedX', "number", ["number"]);
const getAgentSpeedY = Module.cwrap('getAgentSpeedY', "number", ["number"]);
const getNumberOfAgents = Module.cwrap('getNumberOfAgents', "number", []);

create_simulator(100.0, 100.0);
add_random_agents(20, 5.0);

for (let index = 0; index < getNumberOfAgents(); ++index) {
    console.log(`position:(${getAgentX(index)}, ${getAgentY(index)}), speed:(${getAgentSpeedX(index)}, ${getAgentSpeedY(index)})`);
}