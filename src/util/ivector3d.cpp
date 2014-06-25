#include <cmath>

#include "ivector3d.h"

IVector3D::IVector3D() {
    x = y = z = 0;
}

IVector3D::IVector3D(int a, int b, int c) {
  x = a;
  y = b;
  z = c;
}

IVector3D::IVector3D(const IVector3D &v) {
  x = v.x;
  y = v.y;
  z = v.z;
}

IVector3D IVector3D::operator+ (IVector3D v) {
  return IVector3D((x + v.x), (y + v.y), (z + v.z));
}

IVector3D IVector3D::operator- (IVector3D v) {
  return IVector3D((x - v.x), (y - v.y), (z - v.z));
}

Vector3D IVector3D::operator* (double a) {
  return Vector3D((x * a), (y * a), (z * a));
}

IVector3D IVector3D::operator= (IVector3D v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

IVector3D IVector3D::operator+= (IVector3D v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

IVector3D IVector3D::operator*= (double a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

std::ostream& operator<< (std::ostream &out, IVector3D &v) {
  out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return out;
}

void IVector3D::reverse() {
  x = -x;
  y = -y;
  z = -z;
}

void IVector3D::zero() {
  x = 0;
  y = 0;
  z = 0;
}

double IVector3D::length() {
  return sqrt((x * x) + (y * y) + (z * z));
}

double IVector3D::length_squared() {
  return (x * x) + (y * y) + (z * z);
}
