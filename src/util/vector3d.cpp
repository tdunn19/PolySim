#include "vector3d.h"

Vector3D::Vector3D() {
    x = y = z = 0.0;
}

Vector3D::Vector3D(double a, double b, double c) {
  x = a;
  y = b;
  z = c;
}

Vector3D::Vector3D(const Vector3D& v) {
  x = v.x;
  y = v.y;
  z = v.z;
}

Vector3D Vector3D::operator+ (const Vector3D& v) const {
  return Vector3D((x + v.x), (y + v.y), (z + v.z));
}

Vector3D Vector3D::operator- (const Vector3D& v) const {
  return Vector3D((x - v.x), (y - v.y), (z - v.z));
}

Vector3D Vector3D::operator* (double a) const {
  return Vector3D((x * a), (y * a), (z * a));
}

Vector3D Vector3D::operator/ (double a) const {
  return Vector3D((x / a), (y / a), (z / a));
}

Vector3D Vector3D::operator= (const Vector3D& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

Vector3D Vector3D::operator+= (const Vector3D& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vector3D Vector3D::operator-= (const Vector3D& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector3D Vector3D::operator*= (double a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

bool Vector3D::operator==(const Vector3D& v) {
  return (std::fabs(x - v.x) < std::numeric_limits<double>::epsilon() &&
          std::fabs(y - v.y) < std::numeric_limits<double>::epsilon() &&
          std::fabs(z - v.z) < std::numeric_limits<double>::epsilon());
}

std::istream& operator>>(std::istream& in, Vector3D& v) {
  in >> v.x;
  in >> v.y;
  in >> v.z;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& v) {
  out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return out;
}

Vector3D Vector3D::reverse() const {
  return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::normalize() const {
  double mag = length();
  if (mag > 0) {
    return (*this / mag);
  } else {
    return Vector3D();
  }
}

void Vector3D::zero() {
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

double Vector3D::length() const {
  return sqrt((x * x) + (y * y) + (z * z));
}

double Vector3D::lengthSquared() const {
  return (x * x) + (y * y) + (z * z);
}

double Vector3D::dotProduct(const Vector3D& v) const {
  return (v.x * x) + (v.y * y) + (v.z * z);
}

