export module clampedtransform;

import transform;
import clonablecomponent;
import vector3d;

// Position of game object is clamped , can be used to prevent game objects from leaving the screen
export class ClampedTransform: public ClonableComponent<Transform, ClampedTransform> {
    double left, right, top, bottom;
    public:
    ClampedTransform(Vector3D position, double left, double right, double top, double bottom);
    void setPosition(Vector3D position) override;
};
