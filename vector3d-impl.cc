module vector3d;

import <cmath>;

Vector3D Vector3D::operator+(const Vector3D &other) const {
    return Vector3D{x + other.x, y + other.y, z + other.z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
    return Vector3D{x - other.x, y - other.y, z - other.z};
} 

Vector3D &Vector3D::operator+=(const Vector3D &other) {
    *this = *this + other;
    return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &other) {
    *this = *this - other;
    return *this;
} 

Vector3D Vector3D::normalized(){
    double magnitude = std::sqrt(this->x*this->x + this->y*this->y);
    return Vector3D{this->x /magnitude, this->y / magnitude};
}
