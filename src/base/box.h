#ifndef BOX_H
#define BOX_H

#include <cmath>

#include "../util/vector3d.h"
#include "../util/random.h"

class Box {
 public:
  Box();
  Box(double x, double y, double z);
  Box(Vector3D length);

  double distance(const Vector3D& v1, const Vector3D& v2);
  Vector3D pbcDisplacement(const Vector3D& v1, const Vector3D& v2);
  void pbcPosition(Vector3D& pos);
  Vector3D randomPoint(Random& rng);

  Vector3D length;
  Vector3D half_length;
  double volume;
};

#endif
