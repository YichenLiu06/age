module spawner;

import gameobjectcomponent;
import <memory>;

//Cloning spawners should not also clone their queue
std::unique_ptr<Component> Spawner::clone() const {
    return std::make_unique<Spawner>();
}

std::unique_ptr<GameObject> Spawner::spawn() {
    std::unique_ptr<GameObject> prototype = std::move(queue.front());
    queue.pop();
    return std::move(prototype);
}

bool Spawner::isEmpty(){
    return queue.empty();
}

void Spawner::queueSpawn(std::unique_ptr<GameObject> prototype){
    queue.push(std::move(prototype));
}
