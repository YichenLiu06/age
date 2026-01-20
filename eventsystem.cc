export module eventsystem;

import eventhandler;
import eventqueue;
import gameobjectcomponent;
import <memory>;
import <vector>;

export class EventSystem {
    EventQueue &eventQueue;
    public:
    EventSystem(EventQueue &eventQueue);
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
