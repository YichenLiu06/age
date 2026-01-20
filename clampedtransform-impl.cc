module clampedtransform;

import transform;
import vector3d;
import <algorithm>;

ClampedTransform::ClampedTransform(Vector3D position, double left, double right, double top, double bottom): 
ClonableComponent{position}, left{left}, right{right}, top{top}, bottom{bottom} {}

void ClampedTransform::setPosition(Vector3D position){
    this->position.x = std::clamp(position.x, left, right);
    this->position.y = std::clamp(position.y, top, bottom);
}
