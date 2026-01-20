module timersystem;

import timer;
import gameobjectcomponent;
import <memory>;
import <vector>;

void TimerSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    for(const auto &gameObject : gameObjects){
        if(gameObject->getComponent<Timer>()){
            Timer *timer = gameObject->getComponent<Timer>();
            if(timer->isActive()){
                timer->tick();
            }
        }
    }
}
