module eventsystem;

import eventhandler;
import eventqueue;
import gameobjectcomponent;
import <memory>;
import <vector>;
import <iostream>;

EventSystem::EventSystem(EventQueue &eventQueue): eventQueue{eventQueue} {}

void EventSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    // Keep handling events until events are empty
    // Game objects may push events when handling events
    while(!eventQueue.isEmpty()){
        std::string event = eventQueue.getNextEvent();
        for(const auto &gameObject : gameObjects){
            if(gameObject->getComponent<EventHandler>()){
                for(EventHandler *eventHandler : gameObject->getAllComponents<EventHandler>()){
                    if(eventHandler->isActive()){
                        eventHandler->handleEvent(event);
                    }
                }
            }
        }
        eventQueue.popEvent();
    }
}
