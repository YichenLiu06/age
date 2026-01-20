export module collider;

import gameobjectcomponent;
import vector3d;

export class Collider: public Component {
    public:
    // Predicate for intersection between this and another Collider
    virtual bool intersects(const Collider *other) const = 0;
    // Returns normal direction scaled by the length of intersection
    // Assumes that this intersects other
    virtual Vector3D calculateNormal(const Collider *other) const = 0;
};
