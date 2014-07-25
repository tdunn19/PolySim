#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>
#include <limits>

class Vector3D {
 public:
  double x, y, z;

  Vector3D();
  Vector3D(double a, double b, double c);
  Vector3D(const Vector3D& v);
  ~Vector3D();

  Vector3D operator+ (const Vector3D& v) const;
  Vector3D operator- (const Vector3D& v) const;
  friend Vector3D operator* (double a, const Vector3D& v);
  friend Vector3D operator* (const Vector3D& v, double a);
  Vector3D operator/ (double a) const;
  Vector3D operator= (const Vector3D& v);
  Vector3D operator+= (const Vector3D& v);
  Vector3D operator-= (const Vector3D& v);
  Vector3D operator*= (double a);
  Vector3D operator/= (double a);
  bool operator== (const Vector3D& v);
  friend std::istream& operator>> (std::istream& in, Vector3D& v);
  friend std::ostream& operator<< (std::ostream& out, const Vector3D& v);

  void zero();
  double length() const;
  double lengthSquared() const;
  double dotProduct(const Vector3D& v) const;
  Vector3D reverse() const;
  Vector3D normalize() const;
  Vector3D crossProduct(const Vector3D& v) const;
};

#endif // VECTOR3D_H
