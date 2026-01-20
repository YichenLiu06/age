export module transform;
import gameobjectcomponent;
import vector3d;
import clonablecomponent;

export class Transform: public ClonableComponent<Component, Transform> {
    protected:
    Vector3D position;
    public:
    Transform(Vector3D position);
    virtual Vector3D getPosition();
    virtual void setPosition(Vector3D position);
};
