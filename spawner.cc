export module spawner;

import gameobjectcomponent;
import clonablecomponent;
import <memory>;
import <queue>;

export class Spawner: public Component {
    // New game objects to be added to the world during this tick
    std::queue<std::unique_ptr<GameObject>> queue;
    public:
    // Cloning spawners should not also clone their queue
    std::unique_ptr<Component> clone() const override;
    std::unique_ptr<GameObject> spawn();
    bool isEmpty();
    // Spawn a new game object
    void queueSpawn(std::unique_ptr<GameObject> prototype);
};
