export module stopcollisionbehaviour;

import vector3d;
import collider;
import collisionbehaviour;
import gameobjectcomponent;
import clonablecomponent;

export class StopCollisionBehaviour: public ClonableComponent<CollisionBehaviour, StopCollisionBehaviour> {
    public:
    // Push object out of the Collider it is intersecting with
    void collide(Collider *other) override;
};
