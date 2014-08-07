#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>

#include "../util/vector3d.h"

enum ParticleType {
  monomer_type, solvent_type, wall_type, pore_type
};

class Particle {
 public:
  Particle();
  Particle(int index, ParticleType type);
  Particle(int index, double x, double y, double z);
  Particle(int index, double x, double y, double z, ParticleType type);
  Particle(int index, Vector3D pos, ParticleType type);
  Particle(int index, Vector3D pos, Vector3D vel, ParticleType type);
  Particle(int index, Vector3D pos, Vector3D vel, Vector3D force, ParticleType type);
  Particle(const Particle& other);

  int index;
  Vector3D pos;
  Vector3D vel;
  Vector3D force;
  ParticleType type;

  friend std::ostream& operator<< (std::ostream& out, const Particle& particle);
};


#endif
