export module movement;
import gameobjectcomponent;
import transform;
import vector3d;
import clonablecomponent;

export class Movement: public ClonableComponent<Component, Movement> {
    protected:
    Vector3D velocity;
    Vector3D acceleration;
    public:
    Movement(Vector3D velocity = Vector3D{0,0}, Vector3D acceleration = Vector3D{0,0});
    // Modifies parent game object's transform based on velocity and acceleration
    void move();
    virtual Vector3D getVelocity();
    virtual void setVelocity(Vector3D velocity);
    virtual Vector3D getAcceleration();
    virtual void setAcceleration(Vector3D acceleration);
};
