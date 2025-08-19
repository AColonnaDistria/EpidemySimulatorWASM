import * as epidemy from './epidemyMethods.js';
import { Application, Assets, Container, Graphics, Sprite, Circle } from 'pixi.js';

(async () => {
    epidemy.create_simulator(500.0, 500.0);
    epidemy.add_random_agents(20, 5.0);

    const app = new Application();
    await app.init({ background: 'white', resizeTo: window });

    document.body.appendChild(app.canvas);
    const container = new Container();
    app.stage.addChild(container);

    const circleGfx = new Graphics()
        .circle(0, 0, 5.0)
        .fill(0x000000);

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
    app.ticker.add((time) => {
        for (let index = 0; index < numberOfAgents; index++) {
            sprites[index].x = epidemy.getAgentX(index);
            sprites[index].y = epidemy.getAgentY(index);
        }
    });
})();