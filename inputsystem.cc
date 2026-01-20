export module inputsystem;

import controller;
import <memory>;
import <vector>;
import gameobjectcomponent;
import inputhandler;

export class InputSystem {
    std::unique_ptr<Controller> controller;
    public:
    void setController(std::unique_ptr<Controller> controller);
    void unsetController();
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
