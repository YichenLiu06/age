export module gameobjectmanager;

import gameobjectcomponent;
import eventqueue;
import textstatus;
import <memory>;
import <vector>;

export class GameObjectManager {
    // Owning list of all game objects in the world
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    // References to TextStatus and EventQueue to attach to new game objects
    TextStatus &textStatus;
    EventQueue &eventQueue;
    public:
    GameObjectManager(TextStatus &textStatus, EventQueue &eventQueue);
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    void removeGameObject(GameObject *gameObject);
    std::vector<std::unique_ptr<GameObject>> &getGameObjects();
};
