#include "box.h"

Box::Box() {
  length.zero();
  half_length.zero();
  volume = length.x * length.y * length.z;
}

Box::Box(double x, double y, double z) {
  length.x = x;
  length.y = y;
  length.z = z;
  half_length = length / 2.0;
  volume = length.x * length.y * length.z;
}

Box::Box(Vector3D length) : length(length) {
  half_length = length / 2.0;
  volume = length.x * length.y * length.z;
}

double Box::distance(const Vector3D& v1, const Vector3D& v2) const {
  Vector3D dr = pbcDisplacement(v1, v2);
  return dr.length();
}

Vector3D Box::pbcDisplacement(const Vector3D& v1, const Vector3D& v2) const {
  Vector3D dr = v1 - v2;

  if (dr.x > half_length.x) {
    dr.x -= length.x;
  } else if (dr.x < -half_length.x) {
    dr.x += length.x;
  }

  if (dr.y > half_length.y) {
    dr.y -= length.y;
  } else if (dr.y < -half_length.y) {
    dr.y += length.y;
  }

  if (dr.z > half_length.z) {
    dr.z -= length.z;
  } else if (dr.z < -half_length.z) {
    dr.z += length.z;
  }

  return dr;
}

void Box::pbcPosition(Vector3D& pos) const {
  if (pos.x >= length.x) {
    pos.x -= length.x;
  } else if (pos.x < 0) {
    pos.x += length.x;
  }
  
  if (pos.y >= length.y) {
    pos.y -= length.y;
  } else if (pos.y < 0) {
    pos.y += length.y;
  }
  
  if (pos.z >= length.z) {
    pos.z -= length.z;
  } else if (pos.z < 0) {
    pos.z += length.z;
  }
} 

Vector3D Box::randomPoint(Random& rng) const {
  Vector3D min;
  Vector3D max = length;

  return rng.randomVector(min, max);
}
