export module vector3d;

export class Vector3D {
    public:
    // Addition/Subtraction of vectors
    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D &operator+=(const Vector3D &other);
    Vector3D &operator-=(const Vector3D &other);
    // Get unit vector in the same direction as this
    Vector3D normalized();
    double x, y, z;
};

// Scalar multiplication
export Vector3D operator*(double scale, const Vector3D &v) {
    return Vector3D{scale * v.x, scale * v.y, scale * v.z};
}

// Dot product
export double operator*(const Vector3D &u, const Vector3D &v)  {
    return u.x * v.x + u.y * v.y;
}
