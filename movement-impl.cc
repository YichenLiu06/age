module movement;
import transform;
import gameobjectcomponent;
import vector3d;
import <iostream>;

Movement::Movement(Vector3D velocity, Vector3D acceleration): velocity{velocity}, acceleration{acceleration} {}

void Movement::move() {
    Transform* transform = gameObject->getComponent<Transform>();
    transform->setPosition(transform->getPosition() + velocity);
    velocity += acceleration;
}

Vector3D Movement::getVelocity(){
    return velocity;
}

void Movement::setVelocity(Vector3D velocity){
    this->velocity = velocity;
}

Vector3D Movement::getAcceleration(){
    return acceleration;
}

void Movement::setAcceleration(Vector3D acceleration){
    this->acceleration = acceleration;
}
