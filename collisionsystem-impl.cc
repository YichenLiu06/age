module collisionsystem;

import collider;
import collisionbehaviour;
import gameobjectcomponent;
import <iostream>;

void CollisionSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    // Loop through each pair of game objects and handle collisions
    for(const auto &gameObject1 : gameObjects){
        Collider *collider1 = gameObject1->getComponent<Collider>();
        if(gameObject1->getComponent<Collider>() && collider1 && collider1->isActive()){
            for(const auto &gameObject2 : gameObjects){
                Collider *collider2 = gameObject2->getComponent<Collider>();
                if(&gameObject1 != &gameObject2 && collider2 && collider2->isActive()){
                    if(collider1->intersects(collider2)){
                        for(auto *collisionBehaviour : gameObject1->getAllComponents<CollisionBehaviour>()){
                            if(collisionBehaviour->isActive()){
                                collisionBehaviour->collide(collider2);
                            }
                        }
                    }
                }
            }
        }
    }
}
