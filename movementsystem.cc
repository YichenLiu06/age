export module movementsystem;
import gameobjectcomponent;
import movement;
import <memory>;
import <vector>;

export class MovementSystem {
    public:
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
