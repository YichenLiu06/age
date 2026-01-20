export module bouncecollisionbehaviour;

import vector3d;
import collider;
import collisionbehaviour;
import gameobjectcomponent;
import clonablecomponent;

export class BounceCollisionBehaviour: public ClonableComponent<CollisionBehaviour, BounceCollisionBehaviour> {
    public:
    void collide(Collider *other) override;
};
