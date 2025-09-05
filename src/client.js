import * as epidemy from './epidemyMethods.js';
import { Application, Assets, Container, Graphics, Sprite, Circle } from 'pixi.js';

(async () => {
    var TIMER_ID = null;
    var TIME = 0;

    var numberOfAgentsRange = document.getElementById("number-of-agents-range");
    var numberOfInfectedRange = document.getElementById("number-of-infected-range");
    var numberOfImmuneRange = document.getElementById("number-of-immune-range");
    var agentSpeedRange = document.getElementById("agent-speed-range");
    var contaminationProbabilityRange = document.getElementById("contamination-probability-range");
    var contaminationRadiusRange = document.getElementById("contamination-radius-range");
    var healingProbabilityRange = document.getElementById("healing-probability-range");
    var deathProbabilityRange = document.getElementById("death-probability-range");
    var immunityProbabilityRange = document.getElementById("immunity-probability-range");

    var playButton = document.getElementById("play-button");
    var pauseButton = document.getElementById("pause-button");
    var restartButton = document.getElementById("restart-button");

    var sprites;
    var numberOfAgents;

    var AGENT = {
        HEALTHY: 0,
        INFECTED: 1,
        IMMUNE: 2,
        DEAD: 3
    };

    var DATA = {
        SPACE_WH: 500.0,
        P_CONTAMINATION: 0.3,
        CONTAMINATION_RADIUS: 30.0,
        P_HEAL: 0.0125,
        P_DEATH: 0.01,
        P_IMMUNE: 0.005,
        NUMBER_OF_AGENTS: 200,
        AGENTS_SPEED_PER_SECONDS: 100.0,
        NUMBER_OF_INFECTED: 2,
        NUMBER_OF_IMMUNE: 0
    };

    const AGENT_COLORS = {
        [AGENT.HEALTHY]: 0xffff00,
        [AGENT.INFECTED]: 0x008000,
        [AGENT.IMMUNE]:  0xffc0cb,
        [AGENT.DEAD]:    0xc4c4c4,
    }

    const AGENT_COLORS_CHART = {
        [AGENT.HEALTHY]: '#ffff00',
        [AGENT.INFECTED]: '#008000',
        [AGENT.IMMUNE]:  '#ffc0cb',
        [AGENT.DEAD]:    '#c4c4c4',
    };

    const epidemy_container = document.getElementById("epidemy_container");
    const chart_ctx = document.getElementById('chart_container');

    var data = {
        labels: [],
        datasets: [{
            label: 'Healthy',
            data: [],
            backgroundColor: AGENT_COLORS_CHART[AGENT.HEALTHY],
            borderColor: AGENT_COLORS_CHART[AGENT.HEALTHY],
            borderWidth: 1
        },
        {
            label: 'Infected',
            data: [],
            backgroundColor: AGENT_COLORS_CHART[AGENT.INFECTED],
            borderColor: AGENT_COLORS_CHART[AGENT.INFECTED],
            borderWidth: 1
        },
        {
            label: 'Immune',
            data: [],
            backgroundColor: AGENT_COLORS_CHART[AGENT.IMMUNE],
            borderColor: AGENT_COLORS_CHART[AGENT.IMMUNE],
            borderWidth: 1
        },
        {
            label: 'Dead',
            data: [],
            backgroundColor: AGENT_COLORS_CHART[AGENT.DEAD],
            borderColor: AGENT_COLORS_CHART[AGENT.DEAD],
            borderWidth: 1
        }
    ]
    };

    const chart = new Chart(chart_ctx, {
        type: 'line',
        data: data,
        options: {
            animation: false,
            maintainAspectRatio:false,
            responsive:false,	
            scales: {
                x: { type: 'linear', title: { display: true, text: 'Time (s)' } },
                y: { beginAtZero: true }
            },
        }
    });

    function stopTimer() {
        clearInterval(TIMER_ID);
        TIMER_ID = null;
    }

    function initSprites() {
        sprites = [];
        numberOfAgents = epidemy.getNumberOfAgents();

        container.removeChildren();

        for (let index = 0; index < numberOfAgents; index++) {
            const x = epidemy.getAgentX(index) / (DATA.SPACE_WH / 500.0);
            const y = epidemy.getAgentY(index) / (DATA.SPACE_WH / 500.0);

            const sprite = new Sprite(circleTexture);
            sprite.x = x;
            sprite.y = y;

            sprites.push(sprite);

            container.addChild(sprite);
        }

        clearChart();
        drawSprites();
    }

    function clearChart() {
        TIME = 0;

        chart.data.datasets[0].data = [{"x": TIME, "y": epidemy.getNumberOfHealthy()}];
        chart.data.datasets[1].data = [{"x": TIME, "y": epidemy.getNumberOfInfected()}];
        chart.data.datasets[2].data = [{"x": TIME, "y": epidemy.getNumberOfImmune()}];
        chart.data.datasets[3].data = [{"x": TIME, "y": epidemy.getNumberOfDead()}];
    }

    function startTimer() {
        TIMER_ID = setInterval(() => {
            TIME += 0.5;

            chart.data.datasets[0].data.push({"x": TIME, "y": epidemy.getNumberOfHealthy()});
            chart.data.datasets[1].data.push({"x": TIME, "y": epidemy.getNumberOfInfected()});
            chart.data.datasets[2].data.push({"x": TIME, "y": epidemy.getNumberOfImmune()});
            chart.data.datasets[3].data.push({"x": TIME, "y": epidemy.getNumberOfDead()});

            chart.update();
        }, 500);
    }

    function drawSprites() {
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
    }

    function setDefaultValues() {
        numberOfAgentsRange.min = 0;
        numberOfAgentsRange.max = 2500;
        numberOfAgentsRange.step = 1;
        numberOfAgentsRange.value = DATA.NUMBER_OF_AGENTS;
        
        numberOfInfectedRange.min = 0;
        numberOfInfectedRange.max = DATA.NUMBER_OF_AGENTS;
        numberOfInfectedRange.step = 1;
        numberOfInfectedRange.value = DATA.NUMBER_OF_INFECTED;
        
        numberOfImmuneRange.min = 0;
        numberOfImmuneRange.max = DATA.NUMBER_OF_AGENTS;
        numberOfImmuneRange.step = 1;
        numberOfImmuneRange.value = DATA.NUMBER_OF_IMMUNE;

        agentSpeedRange.min = 5;
        agentSpeedRange.max = 300;
        agentSpeedRange.step = 0.1;
        agentSpeedRange.value = DATA.AGENTS_SPEED_PER_SECONDS;
        
        contaminationProbabilityRange.min = 0;
        contaminationProbabilityRange.max = 1;
        contaminationProbabilityRange.step = 0.01;
        contaminationProbabilityRange.value = DATA.P_CONTAMINATION;
        
        contaminationRadiusRange.min = 0;
        contaminationRadiusRange.max = 100;
        contaminationRadiusRange.step = 0.5;
        contaminationRadiusRange.value = DATA.CONTAMINATION_RADIUS;

        healingProbabilityRange.min = 0;
        healingProbabilityRange.max = 1;
        healingProbabilityRange.step = 0.01;
        healingProbabilityRange.value = DATA.P_HEAL;

        deathProbabilityRange.min = 0;
        deathProbabilityRange.max = 1;
        deathProbabilityRange.step = 0.01;
        deathProbabilityRange.value = DATA.P_DEATH;

        immunityProbabilityRange.min = 0;
        immunityProbabilityRange.max = 1;
        immunityProbabilityRange.step = 0.01;
        immunityProbabilityRange.value = DATA.P_IMMUNE;
    }

    function setEvents() {
        playButton.addEventListener("click", () => {
            startTimer();
        });

        pauseButton.addEventListener("click", () => {
            stopTimer();
        });

        restartButton.addEventListener("click", () => {
            epidemy.createSimulator(DATA);
            epidemy.addRandomAgents(DATA);

            initSprites();
        });

        document.querySelectorAll(".var-range").forEach((range) => {
            range.addEventListener("change", () => {
                DATA.P_CONTAMINATION = contaminationProbabilityRange.value;
                DATA.CONTAMINATION_RADIUS = contaminationRadiusRange.value;
                DATA.P_HEAL = healingProbabilityRange.value;
                DATA.P_DEATH = deathProbabilityRange.value;
                DATA.P_IMMUNE = immunityProbabilityRange.value;

                epidemy.setVirusCharacteristics(DATA);
            });
        });
        
        document.querySelectorAll(".var-range-agents").forEach((range) => {
            range.addEventListener("change", () => {
                DATA.NUMBER_OF_AGENTS = numberOfAgentsRange.value;
                DATA.NUMBER_OF_INFECTED = numberOfInfectedRange.value;
                DATA.NUMBER_OF_IMMUNE = numberOfImmuneRange.value;
                DATA.AGENTS_SPEED_PER_SECONDS = agentSpeedRange.value;

                epidemy.createSimulator(DATA);
                epidemy.addRandomAgents(DATA);

                initSprites();
            });
        });
    }

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
    initSprites();
    setDefaultValues();
    setEvents();

    startTimer();
    // Listen for animate update
    app.ticker.add((ticker) => {
        if (TIMER_ID != null) {
            let time = ticker.deltaMS / 1000;
            epidemy.step(time);
            
            drawSprites();
        }
    });
})();