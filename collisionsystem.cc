export module collisionsystem;

import gameobjectcomponent;
import <vector>;
import <memory>;

export class CollisionSystem {
    public:
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
