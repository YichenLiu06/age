export module flappybird;

import world;
import cursescontroller;
import controller;
import cursesview;
import gameobjectcomponent;
import sprite;
import bitmaptexture;
import boxtexture;
import transform;
import clampedtransform;
import pixel;
import timer;
import movement;
import collider;
import boxcollider;
import collisionbehaviour;
import stopcollisionbehaviour;
import bouncecollisionbehaviour;
import inputhandler;
import eventhandler;
import spawner;
import state;
import clonablecomponent;
import vector3d;
import <string>;
import <memory>;
import <iostream>;
import <initializer_list>;
import <cstdlib>;
import <chrono>;

int WIDTH = 78;
int HEIGHT = 20;
int GAP_HEIGHT = 5;
int OBSTACLE_SPEED = 0.5;

long long getMs(){ return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

std::unique_ptr<BoxTexture> obstacleTexture = std::make_unique<BoxTexture>(0,3,0,HEIGHT,'#');
std::unique_ptr<BoxTexture> floorTexture = std::make_unique<BoxTexture>(0,WIDTH,0,1,'^');
std::unique_ptr<BoxTexture> checkpointTexture = std::make_unique<BoxTexture>(0,1,0,HEIGHT,'|');
std::unique_ptr<BitmapTexture> playerTexture = std::make_unique<BitmapTexture>();

class GameStateInputHandler: public ClonableComponent<InputHandler, GameStateInputHandler> {
    public:
    void handleInput(char input){
        if(input == 's'){
            State *state = gameObject->getComponent<State>();
            if(!state->getData("started")){
                state->setData("started", 1);
                state->setData("score", 0);
                gameObject->print(0, "Score: 0");
                gameObject->print(2, " ");
                gameObject->emit("start");
            }
        }
    }
};

class EnvironmentEventHandler: public ClonableComponent<EventHandler, EnvironmentEventHandler> {
    public:
    void handleEvent(const std::string &event) override {
        if(event == "lose"){
            Movement *movement = gameObject->getComponent<Movement>();
            movement->setVelocity(Vector3D{0,0,0});
            movement->setAcceleration(Vector3D{0,0,0});
        }
        if(event == "start"){
            gameObject->destroy();
        }
    }
};

class CheckpointCollisionBehaviour: public ClonableComponent<CollisionBehaviour, CheckpointCollisionBehaviour> {
    public:
    void collide(Collider *other) override {
        if(other->gameObject->name == "Player"){
            gameObject->destroy();
        }
    }
};

class PlayerInputHandler: public ClonableComponent<InputHandler, PlayerInputHandler> {
    public:
    void handleInput(char input) override {
        if(input == ' '){
            Movement *movement = gameObject->getComponent<Movement>();
            movement->setVelocity(Vector3D{0,-1,0});
        }
    }
};

class PlayerCollisionBehaviour: public ClonableComponent<CollisionBehaviour, PlayerCollisionBehaviour> {
    public:
    void collide(Collider *other) override {
        Collider *self = gameObject->getComponent<Collider>();

        if(other->gameObject->name == "Obstacle"){
            gameObject->emit("lose");
        }

        else if(other->gameObject->name == "Checkpoint"){
            gameObject->emit("checkpoint");
        }

        else{
            // Copied from StopCollisionBehaviour, player needs to pass through some Colliders, and stop on others
            Transform *transform= gameObject->getComponent<Transform>();
            Vector3D normal = self->calculateNormal(other);
            transform->setPosition(transform->getPosition() + normal);
        }
    }
};

class PlayerEventHandler: public ClonableComponent<EventHandler, PlayerEventHandler> {
    public:
    void handleEvent(const std::string &event) override {
        if(event == "lose"){
            Movement *movement = gameObject->getComponent<Movement>();
            movement->setVelocity(Vector3D{0,0,0});
            movement->setAcceleration(Vector3D{0,0,0});
            gameObject->getComponent<InputHandler>()->setActive(false);
            gameObject->getComponent<CollisionBehaviour>()->setActive(false);
        }
        if(event == "start"){
            Transform *transform = gameObject->getComponent<Transform>();
            Movement *movement = gameObject->getComponent<Movement>();
            transform->setPosition(Vector3D{5,HEIGHT/2,0});
            movement->setVelocity(Vector3D{0,0,0});
            movement->setAcceleration(Vector3D{0,0.2,0});
            gameObject->getComponent<InputHandler>()->setActive(true);
            gameObject->getComponent<CollisionBehaviour>()->setActive(true);
        }
    }
};

class GameStateEventHandler: public ClonableComponent<EventHandler, GameStateEventHandler> {
    public:
    void handleEvent(const std::string &event) override {
        if(event == "lose"){
            State *state = gameObject->getComponent<State>();
            state->setData("started", 0);
            gameObject->print(2, "You Lose! Press s to play again");
        }
        if(event == "checkpoint"){
            State *state = gameObject->getComponent<State>();
            int score = state->getData("score");
            int highScore = state->getData("highScore");
            score++;
            highScore = std::max(score, highScore);
            state->setData("score", score);
            state->setData("highScore", highScore);
            gameObject->print(0, "Score: " + std::to_string(score));
            gameObject->print(1, "High Score: " + std::to_string(highScore));
        }
    }
};

std::unique_ptr<GameObject> makeObstacle(int x, int y){
    std::unique_ptr<GameObject> obstacle = std::make_unique<GameObject>("Obstacle");
    obstacle->addComponent(std::make_unique<Transform>(Vector3D{x,y,0}));
    obstacle->addComponent(std::make_unique<Movement>(Vector3D{-0.5,0,0}, Vector3D{0,0,0}));
    obstacle->addComponent(std::make_unique<Sprite>(obstacleTexture.get()));
    obstacle->addComponent(std::make_unique<BoxCollider>(0,3,0,HEIGHT));
    obstacle->addComponent(std::make_unique<EnvironmentEventHandler>());
    return obstacle;
}

std::unique_ptr<GameObject> makeCheckpoint(int x){
    std::unique_ptr<GameObject> checkpoint = std::make_unique<GameObject>("Checkpoint");
    checkpoint->addComponent(std::make_unique<Transform>(Vector3D{x,0,0}));
    checkpoint->addComponent(std::make_unique<Movement>(Vector3D{-0.5,0,0}, Vector3D{0,0,0}));
    checkpoint->addComponent(std::make_unique<Sprite>(checkpointTexture.get()));
    checkpoint->addComponent(std::make_unique<BoxCollider>(0,1,0,HEIGHT));
    checkpoint->addComponent(std::make_unique<EnvironmentEventHandler>());
    checkpoint->addComponent(std::make_unique<CheckpointCollisionBehaviour>());

    return checkpoint;
}

class ObstacleSpawnerEventHandler: public ClonableComponent<EventHandler, ObstacleSpawnerEventHandler> {
    public:
    void handleEvent(const std::string &event){
        if(event == "spawnObstacles"){
            Transform *transform = gameObject->getComponent<Transform>();
            Spawner *spawner = gameObject->getComponent<Spawner>();
            int x = transform->getPosition().x;
            int spawnHeight = std::rand() % (HEIGHT-GAP_HEIGHT-1);
            std::unique_ptr<GameObject> topObstacle = makeObstacle(x, spawnHeight - HEIGHT);
            std::unique_ptr<GameObject> bottomObstacle = makeObstacle(x, spawnHeight + GAP_HEIGHT);
            std::unique_ptr<GameObject> checkpoint = makeCheckpoint(x);
            spawner->queueSpawn(std::move(topObstacle));
            spawner->queueSpawn(std::move(bottomObstacle));
            spawner->queueSpawn(std::move(checkpoint));
        }

        if(event == "lose"){
            Timer *timer = gameObject->getComponent<Timer>();
            timer->setActive(false);
        }

        if(event == "start"){
            Timer *timer = gameObject->getComponent<Timer>();
            timer->reset();
            timer->setActive(true);
        }
    }
};

export class FlappyBird {
    public:
    void go(){
        std::srand(getMs());

        playerTexture->addPixel(Pixel{0,0,'('});
        playerTexture->addPixel(Pixel{2,0,'o'});
        playerTexture->addPixel(Pixel{3,0,'>'});
        playerTexture->addPixel(Pixel{1,-1,'/'});
        playerTexture->addPixel(Pixel{2,-1,'\\'});
        playerTexture->addPixel(Pixel{1,1,'\\'});
        playerTexture->addPixel(Pixel{2,1,'/'});

        World world{WIDTH, HEIGHT, true};
        world.setController(std::make_unique<CursesController>());
        world.addView(std::make_unique<CursesView>(WIDTH, HEIGHT));

        std::unique_ptr<GameObject> gameState =  std::make_unique<GameObject>("GameState");
        gameState->addComponent(std::make_unique<Transform>(Vector3D{0,0,0}));
        gameState->addComponent(std::make_unique<State>(std::initializer_list<std::string>{"score", "highScore", "started"}));
        gameState->addComponent(std::make_unique<GameStateEventHandler>());
        gameState->addComponent(std::make_unique<GameStateInputHandler>());

        std::unique_ptr<GameObject> player = std::make_unique<GameObject>("Player");
        player->addComponent(std::make_unique<ClampedTransform>(Vector3D{5,HEIGHT/2,0}, 0, WIDTH, 0, HEIGHT));
        player->addComponent(std::make_unique<Movement>(Vector3D{0,0,0}, Vector3D{0,0,0}));
        player->addComponent(std::make_unique<BoxCollider>(0,4,0,1));
        player->addComponent(std::make_unique<Sprite>(playerTexture.get()));
        player->addComponent(std::make_unique<PlayerCollisionBehaviour>());
        player->addComponent(std::make_unique<PlayerEventHandler>());
        player->addComponent(std::make_unique<PlayerInputHandler>());
        player->getComponent<InputHandler>()->setActive(false);
        player->getComponent<CollisionBehaviour>()->setActive(false);

        std::unique_ptr<GameObject> obstacleSpawner = std::make_unique<GameObject>("ObstacleSpawner");
        obstacleSpawner->addComponent(std::make_unique<Transform>(Vector3D{WIDTH,0,0}));
        obstacleSpawner->addComponent(std::make_unique<Timer>(60, "spawnObstacles"));
        obstacleSpawner->getComponent<Timer>()->setActive(false);
        obstacleSpawner->addComponent(std::make_unique<ObstacleSpawnerEventHandler>());
        obstacleSpawner->addComponent(std::make_unique<Spawner>());

        std::unique_ptr<GameObject> floor = std::make_unique<GameObject>("Obstacle");
        floor->addComponent(std::make_unique<Transform>(Vector3D{0,HEIGHT-1,0}));
        floor->addComponent(std::make_unique<Sprite>(floorTexture.get()));
        floor->addComponent(std::make_unique<BoxCollider>(0,WIDTH,0,1));
            
        world.addGameObject(std::move(gameState));
        world.addGameObject(std::move(obstacleSpawner));
        world.addGameObject(std::move(player));
        world.addGameObject(std::move(floor));
        world.print(0, "Score: 0");
        world.print(1, "High Score: 0");
        world.print(2, "Press s to start");
        world.play();
    }
};
