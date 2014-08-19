#ifndef WALL_H
#define WALL_H

#include <cmath>
#include <vector>

#include "box.h"
#include "polymer.h"
#include "../util/vector3d.h"

class Particle;

class Wall {
 public:
  Wall(Box& box, int num_layers, double density, int pore_width);

  void initialize(int index);
  void placePolymer(Polymer& polymer);

  friend std::ostream& operator<< (std::ostream& out, const Wall& wall);

  Box& box;
  bool has_pore;
  int num_layers;
  int num_particles;
  double density;
  int pore_width;
  double pore_length;
  Vector3D pore_min, pore_max, pore_centre;
  Vector3D wall_spacing;
  IVector3D num_particles_1d;
  IVector3D pore_imin, pore_imax;
  std::vector<Particle> particles;
};


#endif
