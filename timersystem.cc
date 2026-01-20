export module timersystem;

import timer;
import gameobjectcomponent;
import <memory>;
import <vector>;

export class TimerSystem {
    public:
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
