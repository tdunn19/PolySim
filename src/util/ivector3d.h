#ifndef IVECTOR3D_H
#define IVECTOR3D_H

#include <iostream>
#include "vector3d.h"

class IVector3D {
 public:
  int x, y, z;

  // Constructors
  IVector3D();
  IVector3D(int a, int b, int c);
  IVector3D(const IVector3D &v);

  // Operator overloadings
  IVector3D operator+ (IVector3D v);
  IVector3D operator- (IVector3D v);
  Vector3D operator* (double a);
  IVector3D operator= (IVector3D v);
  IVector3D operator+= (IVector3D v);
  IVector3D operator*= (double a);
  friend std::ostream& operator<< (std::ostream &out, IVector3D &v);

  // Other functions
  void reverse();
  void zero();
  double length();
  double length_squared();
};

#endif // IVECTOR3D_H
