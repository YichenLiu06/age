module gameobjectmanager;

import gameobjectcomponent;
import transform;
import eventqueue;
import textstatus;
import <memory>;
import <vector>;
import <algorithm>;
import <iostream>;

GameObjectManager::GameObjectManager(TextStatus &textStatus, EventQueue &eventQueue): textStatus{textStatus}, eventQueue{eventQueue} {}

void GameObjectManager::addGameObject(std::unique_ptr<GameObject> gameObject){
    // Inject references
    gameObject->setTextStatus(&textStatus); 
    gameObject->setEventQueue(&eventQueue);
    // Game objects are ordered by z-index 
    auto it = std::lower_bound(gameObjects.begin(), gameObjects.end(), gameObject, 
        [](const std::unique_ptr<GameObject> &a, const std::unique_ptr<GameObject> &b){
            return a->getComponent<Transform>()->getPosition().z < b->getComponent<Transform>()->getPosition().z; 
        });
    gameObjects.insert(it, std::move(gameObject));
}

void GameObjectManager::removeGameObject(GameObject *gameObject){
    gameObjects.erase(std::find_if(gameObjects.begin(), gameObjects.end(), [gameObject](const std::unique_ptr<GameObject> &other){return gameObject == other.get();}));
}

std::vector<std::unique_ptr<GameObject>> &GameObjectManager::getGameObjects(){
    return gameObjects;
}
