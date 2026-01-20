export module boxcollider;

import vector3d;
import collider;
import gameobjectcomponent;
import clonablecomponent;

export class BoxCollider: public ClonableComponent<Collider, BoxCollider> {
    public:
    // Dimensions of BoxCollider
    double top, bottom, left, right;
    BoxCollider(double left, double right, double top, double bottom);
   
    bool intersects(const Collider *other) const override;
    Vector3D calculateNormal(const Collider *other) const override;
};
