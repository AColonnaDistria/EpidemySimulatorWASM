import * as epidemy from './epidemyMethods.js';

epidemy.create_simulator(100.0, 100.0);
epidemy.add_random_agents(20, 5.0);

for (let index = 0; index < epidemy.getNumberOfAgents(); ++index) {
    console.log(`position:(${epidemy.getAgentX(index)}, ${epidemy.getAgentY(index)}), speed:(${epidemy.getAgentSpeedX(index)}, ${epidemy.getAgentSpeedY(index)})`);
}