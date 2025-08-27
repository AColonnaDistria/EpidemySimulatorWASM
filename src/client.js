import * as epidemy from './epidemyMethods.js';
import { Application, Assets, Container, Graphics, Sprite, Circle } from 'pixi.js';

(async () => {
    var AGENT = {
        HEALTHY: 0,
        INFECTED: 1,
        IMMUNE: 2,
        DEAD: 3
    };

    var DATA = {
        SPACE_WH: 500.0,
        P_CONTAMINATION: 0.05,
        CONTAMINATION_RADIUS: 10.0,
        P_HEAL: 0.05,
        P_DEATH: 0.001,
        P_IMMUNE: 0.005,
        NUMBER_OF_AGENTS: 500,
        AGENTS_SPEED_PER_SECONDS: 150.0,
        NUMBER_OF_INFECTED: 20,
        NUMBER_OF_IMMUNE: 2
    };

    const AGENT_COLORS = {
        [AGENT.HEALTHY]: 0xffff00,
        [AGENT.INFECTED]: 0x008000,
        [AGENT.IMMUNE]:  0xffc0cb,
        [AGENT.DEAD]:    0xc4c4c4,
    }

    const epidemy_container = document.getElementById("epidemy_container");

    epidemy.createSimulator(DATA);
    epidemy.addRandomAgents(DATA);

    const app = new Application();
    await app.init({ background: 'white', resizeTo: epidemy_container });

    epidemy_container.appendChild(app.canvas);
    const container = new Container();
    app.stage.addChild(container);

    const circleGfx = new Graphics()
        .circle(0, 0, 5.0 / (DATA.SPACE_WH / 500.0))
        .fill(0xffffff);

    const circleTexture = app.renderer.generateTexture(circleGfx);
    const sprites = [];
    const numberOfAgents = epidemy.getNumberOfAgents();

    for (let index = 0; index < numberOfAgents; index++) {
        const x = epidemy.getAgentX(index) / (DATA.SPACE_WH / 500.0);
        const y = epidemy.getAgentY(index) / (DATA.SPACE_WH / 500.0);

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
            if (sprites[index] != null) {
                let state = epidemy.getAgentState(index);

                if (state != AGENT.DEAD) {
                    sprites[index].x = epidemy.getAgentX(index) / (DATA.SPACE_WH / 500.0);
                    sprites[index].y = epidemy.getAgentY(index) / (DATA.SPACE_WH / 500.0);

                    sprites[index].tint = AGENT_COLORS[state] ?? 0xffffff;
                }
                else {
                    container.removeChild(sprites[index]);
                    sprites[index] = null;
                }
            }
        }
    });
})();