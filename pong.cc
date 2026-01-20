export module pong;

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

int WIDTH = 78;
int HEIGHT = 20;

class GameStateInputHandler: public ClonableComponent<InputHandler, GameStateInputHandler> {
    public:
    void handleInput(char input){
        if(input == ' '){
            State *state = gameObject->getComponent<State>();
            if(!state->getData("started")){
                state->setData("started", 1);
                gameObject->print(2, "");
                gameObject->emit("start");
            }
        }
    }
};

class GameStateEventHandler: public ClonableComponent<EventHandler, GameStateEventHandler> {
    public:
    void handleEvent(const std::string &event) {
        if(event == "player1Win"){
            State *state = gameObject->getComponent<State>();
            int player1Score = state->getData("player1Score");
            player1Score++;
            state->setData("player1Score", player1Score);
            gameObject->print(0, "Player 1 Score: " + std::to_string(player1Score));
            if(state->getData("started")){
                state->setData("started", 0);
                gameObject->print(2, "Press space to start");
                gameObject->emit("reset");
            }
        }

        if(event == "player2Win"){
            State *state = gameObject->getComponent<State>();
            int player2Score = state->getData("player2Score");
            player2Score++;
            state->setData("player2Score", player2Score);
            gameObject->print(1, "Player 2 Score: " + std::to_string(player2Score));
            if(state->getData("started")){
                state->setData("started", 0);
                gameObject->print(2, "Press space to start");
                gameObject->emit("reset");
            }
        }
    }
};

class Goal1CollisionBehaviour: public ClonableComponent<CollisionBehaviour, Goal1CollisionBehaviour> {
    public:
    void collide(Collider *other) override {
        gameObject->emit("player2Win");
    }
};

class Goal2CollisionBehaviour: public ClonableComponent<CollisionBehaviour, Goal2CollisionBehaviour> {
    public: 
    void collide(Collider *other) override {
        gameObject->emit("player1Win");
    }
};

class BallWinEventHandler : public ClonableComponent<EventHandler, BallWinEventHandler> {
    void handleEvent(const std::string &event) {
        if(event == "reset"){
            Transform *transform = gameObject->getComponent<Transform>();
            Movement *movement = gameObject->getComponent<Movement>();
            transform->setPosition(Vector3D{WIDTH/2,HEIGHT/2,0});
            movement->setVelocity(Vector3D{0,0,0});
            movement->setAcceleration(Vector3D{0,0,0});
        }
        if(event == "start"){
            Transform *transform = gameObject->getComponent<Transform>();
            Movement *movement = gameObject->getComponent<Movement>();
            gameObject->getComponent<Movement>();
            transform->setPosition(Vector3D{WIDTH/2,HEIGHT/2,0});
            movement->setVelocity(Vector3D{0.5,0.5,0});
            movement->setAcceleration(Vector3D{0,0.5,0});
        }
    }
};

class Paddle1EventHandler : public ClonableComponent<EventHandler, Paddle1EventHandler> {
    void handleEvent(const std::string &event) {
        if(event == "reset"){
            Transform *transform = gameObject->getComponent<Transform>();
            transform->setPosition(Vector3D{5,0,0});
            gameObject->getComponent<InputHandler>()->setActive(false);
        }

        if(event == "start"){
            gameObject->getComponent<InputHandler>()->setActive(true);
        }
    }
};

class Paddle2EventHandler : public ClonableComponent<EventHandler, Paddle2EventHandler> {
    void handleEvent(const std::string &event) {
        if(event == "reset"){
            Transform *transform = gameObject->getComponent<Transform>();
            transform->setPosition(Vector3D{WIDTH-1-5,0,0});
            gameObject->getComponent<InputHandler>()->setActive(false);
        }

        if(event == "start"){
            gameObject->getComponent<InputHandler>()->setActive(true);
        }
    }
};

class UpDownInputHandler : public ClonableComponent<InputHandler, UpDownInputHandler> {
    char up, down;
    public:
    UpDownInputHandler(char up, char down): up{up}, down{down} {}
    void handleInput(char input) override {
        if(input == up){
            Transform *transform = gameObject->getComponent<Transform>();
            transform->setPosition(transform->getPosition() + Vector3D{0,-1,0});
        }
        if(input == down){
            Transform *transform = gameObject->getComponent<Transform>();
            transform->setPosition(transform->getPosition() + Vector3D{0,1,0});
        }
    }
};


export class Pong {
    public:
    void go(){

        World world{WIDTH, HEIGHT, true};

        world.setController(std::make_unique<CursesController>());

        world.addView(std::make_unique<CursesView>(WIDTH, HEIGHT));

        std::unique_ptr<GameObject> gameState =  std::make_unique<GameObject>("GameState");
        gameState->addComponent(std::make_unique<Transform>(Vector3D{0,0,0}));
        gameState->addComponent(std::make_unique<State>(std::initializer_list<std::string>{"player1Score", "player2Score", "started"}));
        gameState->addComponent(std::make_unique<GameStateInputHandler>());
        gameState->addComponent(std::make_unique<GameStateEventHandler>());
        
        std::unique_ptr<GameObject> ball =  std::make_unique<GameObject>("Ball");
        ball->addComponent(std::make_unique<Transform>(Vector3D{WIDTH/2,HEIGHT/2,0}));
        ball->addComponent(std::make_unique<Sprite>('O'));
        ball->addComponent(std::make_unique<Movement>(Vector3D{0,0,0}, Vector3D{0,0,0}));
        ball->addComponent(std::make_unique<BoxCollider>(0,1,0,1));
        ball->addComponent(std::make_unique<BounceCollisionBehaviour>());
        ball->addComponent(std::make_unique<BallWinEventHandler>());

        std::unique_ptr<BoxTexture> goalTexture = std::make_unique<BoxTexture>(0,1,0,HEIGHT,'#');

        std::unique_ptr<GameObject> goal1 = std::make_unique<GameObject>("Goal1");
        goal1->addComponent(std::make_unique<Transform>(Vector3D{0,0,0}));
        goal1->addComponent(std::make_unique<Sprite>(goalTexture.get()));
        goal1->addComponent(std::make_unique<BoxCollider>(0,1,0,HEIGHT));
        goal1->addComponent(std::make_unique<Goal1CollisionBehaviour>());

        std::unique_ptr<GameObject> goal2 = std::make_unique<GameObject>("Goal2");
        goal2->addComponent(std::make_unique<Transform>(Vector3D{WIDTH-1,0,0}));
        goal2->addComponent(std::make_unique<Sprite>(goalTexture.get()));
        goal2->addComponent(std::make_unique<BoxCollider>(0,1,0,HEIGHT));
        goal2->addComponent(std::make_unique<Goal2CollisionBehaviour>());

        std::unique_ptr<BoxTexture> paddleTexture = std::make_unique<BoxTexture>(0,1,0,5,'#');

        std::unique_ptr<GameObject> paddle1 = std::make_unique<GameObject>("Paddle1");
        paddle1->addComponent(std::make_unique<ClampedTransform>(Vector3D{5,0,0}, 0, WIDTH, 0, HEIGHT-5));
        paddle1->addComponent(std::make_unique<Sprite>(paddleTexture.get()));
        paddle1->addComponent(std::make_unique<UpDownInputHandler>('w', 's'));
        paddle1->getComponent<InputHandler>()->setActive(false);
        paddle1->addComponent(std::make_unique<BoxCollider>(0,1,0,5));
        paddle1->addComponent(std::make_unique<Paddle1EventHandler>());

        std::unique_ptr<GameObject> paddle2 =  std::make_unique<GameObject>("Paddle2");
        paddle2->addComponent(std::make_unique<ClampedTransform>(Vector3D{WIDTH-1-5,0,0}, 0, WIDTH, 0, HEIGHT-5));
        paddle2->addComponent(std::make_unique<Sprite>(paddleTexture.get()));
        paddle2->addComponent(std::make_unique<UpDownInputHandler>('i', 'k'));
        paddle2->getComponent<InputHandler>()->setActive(false);
        paddle2->addComponent(std::make_unique<BoxCollider>(0,1,0,5));
        paddle2->addComponent(std::make_unique<Paddle2EventHandler>());

        world.addGameObject(std::move(gameState));
        world.addGameObject(std::move(ball));
        world.addGameObject(std::move(goal1));
        world.addGameObject(std::move(goal2));
        world.addGameObject(std::move(paddle1));
        world.addGameObject(std::move(paddle2));
        world.print(0, "Player 1 Score: 0");
        world.print(1, "Player 2 Score: 0");
        world.print(2, "Press space to start");
        world.play();
    }
};
