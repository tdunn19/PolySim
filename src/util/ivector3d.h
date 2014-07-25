#ifndef IVECTOR3D_H
#define IVECTOR3D_H

#include <iostream>
#include <cmath>

class IVector3D {
 public:
  int x, y, z;

  IVector3D();
  IVector3D(int a, int b, int c);
  IVector3D(const IVector3D &v);
  ~IVector3D();

  IVector3D operator+ (const IVector3D& v) const;
  IVector3D operator- (const IVector3D& v) const;
  friend IVector3D operator* (int a, const IVector3D& v);
  friend IVector3D operator* (const IVector3D& v, int a);
  IVector3D operator= (const IVector3D& v);
  IVector3D operator+= (const IVector3D& v);
  IVector3D operator-= (const IVector3D& v);
  IVector3D operator*= (int a);
  bool operator== (const IVector3D& v);
  friend std::istream& operator>> (std::istream &in, IVector3D& v);
  friend std::ostream& operator<< (std::ostream &out, const IVector3D& v);

  void zero();
  double length() const;
  double lengthSquared() const;
  IVector3D reverse() const;
};

#endif // IVECTOR3D_H
