module spawnsystem;

import <vector>;
import <memory>;
import spawner;
import gameobjectcomponent;
import gameobjectmanager;

void SpawnSystem::update(GameObjectManager &gameObjectManager){
    const std::vector<std::unique_ptr<GameObject>> &gameObjects = gameObjectManager.getGameObjects();
    std::vector<Spawner*> activeSpawners;
    for(const auto &gameObject : gameObjects){
        if(gameObject->getComponent<Spawner>()){
            Spawner *spawner = gameObject->getComponent<Spawner>();
            if(!spawner->isEmpty()){
                activeSpawners.push_back(spawner);
            }
        }
    }
    for(Spawner *spawner : activeSpawners){
        while(!spawner->isEmpty()){
            gameObjectManager.addGameObject(spawner->spawn());
        }
    }
    activeSpawners.clear();
}
