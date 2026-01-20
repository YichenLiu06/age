export module collisionbehaviour;

import vector3d;
import collider;
import gameobjectcomponent;

export class CollisionBehaviour: public Component {
    public:
    // Executed on collision
    virtual void collide(Collider *other) = 0;
};
