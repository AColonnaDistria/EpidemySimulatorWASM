import * as epidemy from './epidemyMethods.js';
import { Application, Assets, Container, Graphics, Sprite, Circle } from 'pixi.js';

(async () => {
    var AGENT_HEALTHY = 0;
    var AGENT_INFECTED = 1;
    var AGENT_IMMUNE = 2;
    var AGENT_DEAD = 3;

    const AGENT_COLORS = {
        [AGENT_HEALTHY]: 0xffff00,
        [AGENT_INFECTED]: 0x008000,
        [AGENT_IMMUNE]:  0xffc0cb,
        [AGENT_DEAD]:    0xc4c4c4,
    }

    const epidemy_container = document.getElementById("epidemy_container");

    epidemy.create_simulator(500.0, 500.0, 0.05, 30.0);
    epidemy.add_random_agents(50, 150.0, 10, 2);

    const app = new Application();
    await app.init({ background: 'white', resizeTo: epidemy_container });

    epidemy_container.appendChild(app.canvas);
    const container = new Container();
    app.stage.addChild(container);

    const circleGfx = new Graphics()
        .circle(0, 0, 5.0)
        .fill(0xffffff);

    const circleTexture = app.renderer.generateTexture(circleGfx);
    const sprites = [];
    const numberOfAgents = epidemy.getNumberOfAgents();

    for (let index = 0; index < numberOfAgents; index++) {
        const x = epidemy.getAgentX(index);
        const y = epidemy.getAgentY(index);

        const sprite = new Sprite(circleTexture);
        sprite.x = x;
        sprite.y = y;

        sprites.push(sprite);

        container.addChild(sprite);
    }

    // Listen for animate update
    app.ticker.add((ticker) => {
        epidemy.step(ticker.deltaMS / 1000);

        for (let index = 0; index < numberOfAgents; index++) {
            sprites[index].x = epidemy.getAgentX(index);
            sprites[index].y = epidemy.getAgentY(index);

            sprites[index].tint = AGENT_COLORS[epidemy.getAgentState(index)] ?? 0xffffff;
        }
    });
})();