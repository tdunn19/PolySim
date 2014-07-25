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

IVector3D::~IVector3D() {
}

IVector3D IVector3D::operator+ (const IVector3D& v) const {
  return IVector3D((x + v.x), (y + v.y), (z + v.z));
}

IVector3D IVector3D::operator- (const IVector3D& v) const {
  return IVector3D((x - v.x), (y - v.y), (z - v.z));
}

IVector3D operator* (int a, const IVector3D& v) {
  return IVector3D((v.x * a), (v.y * a), (v.z * a));
}

IVector3D operator* (const IVector3D& v, int a) {
  return a * v;
}

IVector3D IVector3D::operator= (const IVector3D& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

IVector3D IVector3D::operator+= (const IVector3D& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

IVector3D IVector3D::operator-= (const IVector3D& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

IVector3D IVector3D::operator*= (int a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

bool IVector3D::operator== (const IVector3D& v) {
  return ((x == v.x) && (y == v.y) && (z == v.z));
}

std::istream& operator>> (std::istream& in, IVector3D& v) {
  in >> v.x;
  in >> v.y;
  in >> v.z;
  return in;
}

std::ostream& operator<< (std::ostream &out, const IVector3D &v) {
  out << v.x << " " << v.y << " " << v.z;
  return out;
}

void IVector3D::zero() {
  x = 0;
  y = 0;
  z = 0;
}

double IVector3D::length() const {
  return sqrt((x * x) + (y * y) + (z * z));
}

double IVector3D::lengthSquared() const {
  return (x * x) + (y * y) + (z * z);
}

IVector3D IVector3D::reverse() const {
  return IVector3D(-x, -y, -z);
}

