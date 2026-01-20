module inputsystem;

import controller;
import <memory>;
import <vector>;
import gameobjectcomponent;
import inputhandler;

void InputSystem::setController(std::unique_ptr<Controller> controller){
    this->controller = std::move(controller);
}

void InputSystem::unsetController(){
    this->controller = nullptr;
}

void InputSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    // Query input from controller
   char input = controller->getInput();
    for(const auto &gameObject : gameObjects){
        if(gameObject->getComponent<InputHandler>()){
            for(auto *inputHandler : gameObject->getAllComponents<InputHandler>()){
                if(inputHandler->isActive()){
                    //Forward input to game object
                    inputHandler->handleInput(input);
                }
            }
        }
    } 
}
