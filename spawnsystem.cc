export module spawnsystem;

import gameobjectcomponent;
import gameobjectmanager;
import spawner;
import <vector>;
import <memory>;

export class SpawnSystem{
    public:
    void update(GameObjectManager &gameObjectManager);
};
