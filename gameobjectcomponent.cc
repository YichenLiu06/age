export module gameobjectcomponent;

import textstatus;
import eventqueue;
import <vector>;
import <memory>;
import <algorithm>;
import <string>;
import <ranges>;

export class Component;
export class GameObject;

class Component{
    bool active = true;
    public:
    GameObject* gameObject;
    virtual std::unique_ptr<Component> clone() const = 0;
    void setActive(bool active);
    bool isActive();
    virtual ~Component() = default;  
};

class GameObject {
    std::vector<std::unique_ptr<Component>> components;
    // Flag for whether or not this game object should be destroyed at the end of this tick
    bool destroyed = false;
    // Counter for number of ticks out of view before game object is destroyed
    int lifetime = 10;
    // Base number of ticks out of view before game object is destroyed
    const int baseLifetime = 10;
    // Reference to TextStatus for printing text
    TextStatus *textStatus;
    // Reference to EventQueue for emitting global events
    EventQueue *eventQueue;
    public:
    std::string name;
    GameObject(std::string name);
    void destroy();
    bool isDestroyed();
    int getLifetime();
    // Return a heap allocated copy of this game object
    virtual std::unique_ptr<GameObject> clone() const;
    // References are injected when game objects are added to the world
    void setTextStatus(TextStatus* textStatus);
    void setEventQueue(EventQueue* eventQueue);
    void setLifetime(int lifetime);
    void resetLifetime();
    // Print text
    void print(int line, const std::string &msg);
    // Emit events
    void emit(const std::string &event);
    void addComponent(std::unique_ptr<Component> component);
    void removeComponent(Component *component);
    // Overridable method for game programmer to implement custom logic
    virtual void update();
    template <typename T> T* getComponent() {
        auto it =  std::find_if(components.begin(), components.end(), 
            [](auto &component){return dynamic_cast<T*>(component.get()) != nullptr;});
        if(it != components.end()) return dynamic_cast<T*>((*it).get());
        else return nullptr;
    }
    template <typename T> auto getAllComponents() {
        return components 
            | std::views::transform([](auto &component){return dynamic_cast<T*>(component.get());}) 
            | std::views::filter([](auto *component){return component != nullptr;});
    }
};
