module world;
import inputsystem;
import graphicssystem;
import controller;
import collider;
import boxcollider;
import transform;
import boxtexture;
import sprite;
import gameobjectcomponent; 
import gameobjectmanager;
import spawnsystem;
import timersystem;
import eventqueue;
import eventsystem;
import vector3d;
import textstatus;
import view;
import <vector>;
import <memory>;
import <algorithm>;
import <iostream>;
import <chrono>;

World::World(int width, int height, bool solid): 
width{width}, height{height}, solid{solid}, textStatus{3}, graphicsSystem{textStatus}, eventSystem{eventQueue}, gameObjectManager{textStatus, eventQueue} {
    int BORDER_SIZE = 200;
    // If view border is defined as solid, add Colliders around the view
    if(solid){
        std::unique_ptr<GameObject> leftBorder = std::make_unique<GameObject>("Border1");
        std::unique_ptr<GameObject> rightBorder = std::make_unique<GameObject>("Border2");
        std::unique_ptr<GameObject> topBorder = std::make_unique<GameObject>("Border3");
        std::unique_ptr<GameObject> bottomBorder = std::make_unique<GameObject>("Border4");
        leftBorder->addComponent(std::make_unique<BoxCollider>(0, BORDER_SIZE, 0, BORDER_SIZE));
        leftBorder->addComponent(std::make_unique<Transform>(Vector3D{-BORDER_SIZE, -BORDER_SIZE/2, 0}));
        rightBorder->addComponent(std::make_unique<BoxCollider>(0, BORDER_SIZE, 0, BORDER_SIZE));
        rightBorder->addComponent(std::make_unique<Transform>(Vector3D{width, -BORDER_SIZE/2, 0}));
        topBorder->addComponent(std::make_unique<BoxCollider>(0, BORDER_SIZE, 0, BORDER_SIZE));
        topBorder->addComponent(std::make_unique<Transform>(Vector3D{-BORDER_SIZE/2, -BORDER_SIZE, 0}));
        bottomBorder->addComponent(std::make_unique<BoxCollider>(0, BORDER_SIZE, 0, BORDER_SIZE));
        bottomBorder->addComponent(std::make_unique<Transform>(Vector3D{-BORDER_SIZE/2, height, 0}));
        addGameObject(std::move(leftBorder));
        addGameObject(std::move(rightBorder));
        addGameObject(std::move(topBorder));
        addGameObject(std::move(bottomBorder));
    }
}

void World::update(){
    // Call systems in defined order 
    inputSystem.update(getGameObjects());
    movementSystem.update(getGameObjects());
    collisionSystem.update(getGameObjects());
    for(const auto &gameObject : getGameObjects()){
        gameObject->update();
    }
    timerSystem.update(getGameObjects());
    spawnSystem.update(gameObjectManager);
    eventSystem.update(getGameObjects());
    graphicsSystem.update(getGameObjects());
    for(auto it = getGameObjects().begin(); it != getGameObjects().end();){
        auto &gameObject = *it;
        if(gameObject->isDestroyed()){
            removeGameObject(gameObject.get());
        }
        else ++it;
    }
}

long long getMs(){ return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

void World::play(){
    long long lastTick = getMs();
    // Call update every 50ms
    while(true){
        if(getMs() - lastTick > 50){
            update();
            lastTick = getMs();
        }
    }
}

void World::addGameObject(std::unique_ptr<GameObject> gameObject){
    gameObjectManager.addGameObject(std::move(gameObject)); 
}
void World::removeGameObject(GameObject *gameObject){ gameObjectManager.removeGameObject(gameObject); }

void World::addView(std::unique_ptr<View> view){
    graphicsSystem.addView(std::move(view));
}

void World::removeView(View * view){
    graphicsSystem.removeView(view);
}

void World::print(int line, const std::string &msg){
    textStatus.setLine(line, msg);
}

void World::setController(std::unique_ptr<Controller> controller){
    inputSystem.setController(std::move(controller));
}

void World::unsetController(){
    inputSystem.unsetController();
}

const std::vector<std::unique_ptr<GameObject>> &World::getGameObjects(){ return gameObjectManager.getGameObjects(); }
