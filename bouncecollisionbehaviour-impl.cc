module bouncecollisionbehaviour;

import vector3d;
import collider;
import collisionbehaviour;
import gameobjectcomponent;
import transform;
import movement;
import <iostream>;

// Velocity in the direction of collision normal gets inverted
void BounceCollisionBehaviour::collide(Collider *other) {
    Collider *self = gameObject->getComponent<Collider>();
    Transform *transform= gameObject->getComponent<Transform>();
    Movement *movement = gameObject->getComponent<Movement>();
    Vector3D normal = self->calculateNormal(other);
    Vector3D unitNormal = normal.normalized();
    // Cancel out acceleration so object doesn't bounce higher than it was dropped from
    movement->setVelocity(movement->getVelocity() - movement->getAcceleration());
    double normalComponentMagnitude = movement->getVelocity() * unitNormal;
    Vector3D normalComponent = normalComponentMagnitude * unitNormal;
    movement->setVelocity(movement->getVelocity() - 2*normalComponent);
}
