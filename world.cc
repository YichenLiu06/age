
export module world;
import inputsystem;
import graphicssystem;
import movementsystem;
import collisionsystem;
import timersystem;
import controller;
import gameobjectcomponent;   
import gameobjectmanager;
import eventqueue;
import eventsystem;
import gameobjectmanager;
import spawnsystem;
import textstatus;
import view;
import <vector>;
import <memory>;


export class World {
    // Border dimensions
    const int width;
    const int height;
    // Border type (solid or view)
    const bool solid;
    EventQueue eventQueue;
    TextStatus textStatus;
    GameObjectManager gameObjectManager;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    CollisionSystem collisionSystem;
    GraphicsSystem graphicsSystem;
    SpawnSystem spawnSystem;
    TimerSystem timerSystem;
    EventSystem eventSystem;
    public:
    World(int width = 78, int height = 20, bool solid = true);
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    void removeGameObject(GameObject *gameObject);
    void addView(std::unique_ptr<View> view);
    void removeView(View *view);
    void setController(std::unique_ptr<Controller> controller);
    void print(int line, const std::string &msg);
    void unsetController();
    const std::vector<std::unique_ptr<GameObject>> &getGameObjects();
    // Game tick
    void update();
    // Start the simulation
    virtual void play();
};
