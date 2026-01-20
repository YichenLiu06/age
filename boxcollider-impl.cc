module boxcollider;

import vector3d;
import collider;
import gameobjectcomponent;
import transform;
import <algorithm>;
import <iostream>;

BoxCollider::BoxCollider(double left, double right, double top, double bottom): 
    top{top}, bottom{bottom}, left{left}, right{right} {}

bool BoxCollider::intersects(const Collider *other) const {
    Transform *selfTransform = gameObject->getComponent<Transform>();
    Vector3D selfPosition = selfTransform->getPosition();
    Transform *otherTransform = other->gameObject->getComponent<Transform>();
    Vector3D otherPosition = otherTransform->getPosition();

    if(const BoxCollider *box = dynamic_cast<const BoxCollider*>(other)){
        
        // Conditional checks that box is NOT outside of other
        if(
            !((selfPosition.y + bottom) <= (otherPosition.y + box->top)) && 
            !((selfPosition.y + top) >= (otherPosition.y + box->bottom)) && 
            !((selfPosition.x + right) <= (otherPosition.x + box->left)) && 
            !((selfPosition.x + left) >= (otherPosition.x + box->right))
        ) {
            return true;
        }
            
        return false;
    }
    // If there are other types of colliders and intersection between them is not defined, return false
    return false;
}

// Assumes that there is an intersection between this and other
Vector3D BoxCollider::calculateNormal(const Collider *other) const {
    Transform *selfTransform = gameObject->getComponent<Transform>();
    Vector3D selfPosition = selfTransform->getPosition();
    Transform *otherTransform = other->gameObject->getComponent<Transform>();
    Vector3D otherPosition = otherTransform->getPosition();
    
    if(const BoxCollider *box = dynamic_cast<const BoxCollider*>(other)){
        // length of overlap along the direction that minimizes overlap
        double minOverlap = __INT_MAX__;
        Vector3D normalDirection;
        // overlap calculated by subtracting higher dimension by lower dimension, e.g. right - left
        double rightOverlap = (selfPosition.x + right) - (otherPosition.x + box->left);
        double leftOverlap = (otherPosition.x + box->right) - (selfPosition.x + left);
        double bottomOverlap = (selfPosition.y + bottom) - (otherPosition.y + box->top);
        double topOverlap = (otherPosition.y + box->bottom) - (selfPosition.y + top);
        
        if(rightOverlap < minOverlap){
            minOverlap = rightOverlap;
            normalDirection = Vector3D{-1,0,0};
        }
        if(leftOverlap < minOverlap){
            minOverlap = leftOverlap;
            normalDirection = Vector3D{1,0,0};
        }
        if(bottomOverlap < minOverlap){
            minOverlap = bottomOverlap;
            normalDirection = Vector3D{0,-1,0};
        }
        if(topOverlap < minOverlap){
            minOverlap = topOverlap;
            normalDirection = Vector3D{0,1,0};
        }
        return minOverlap * normalDirection;
    }
    return Vector3D{0,0,0};
}
