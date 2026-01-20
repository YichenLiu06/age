module movementsystem;
import movement;
import gameobjectcomponent;
import <memory>;
import <vector>;

void MovementSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    for(const auto &gameObject : gameObjects){
        if(gameObject->getComponent<Movement>()){
            Movement *movement = gameObject->getComponent<Movement>();
            movement->move();
        }
    }
}
