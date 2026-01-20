module transform;
import gameobjectcomponent;

Transform::Transform(Vector3D position): position{position} {};

Vector3D Transform::getPosition(){
    return position;
}

void Transform::setPosition(Vector3D position){
    this->position = position;
}
