module stopcollisionbehaviour;

import vector3d;
import collider;
import collisionbehaviour;
import gameobjectcomponent;
import transform;
import <iostream>;

void StopCollisionBehaviour::collide(Collider *other) {
    Collider *self = gameObject->getComponent<Collider>();
    Transform *transform= gameObject->getComponent<Transform>();
    // Normal is the normal direction of the collision scaled by intersection length
    Vector3D normal = self->calculateNormal(other);
    // Push game object out
    transform->setPosition(transform->getPosition() + normal);
}
