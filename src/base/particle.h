#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <vector>

#include "../util/vector3d.h"

class Wall;

enum ParticleType {
  monomer_type, solvent_type, wall_type, pore_type
};

enum ParticleSide {
  cis, pore, trans, none
};

class Particle {
 public:
  typedef std::vector<Particle>::iterator Iterator;
  
  Particle();
  Particle(int index, ParticleType type);
  Particle(int index, double x, double y, double z);
  Particle(int index, double x, double y, double z, ParticleType type);
  Particle(int index, Vector3D pos, ParticleType type);
  Particle(int index, Vector3D pos, Vector3D vel, ParticleType type);
  Particle(int index, Vector3D pos, Vector3D vel, Vector3D force, ParticleType type);
  Particle(const Particle& other);

  void updateSide(const Wall& wall);
  bool isInPore(const Wall& wall);
  bool isInWall(const Wall& wall);

  int index;
  Vector3D pos;
  Vector3D vel;
  Vector3D force;
  ParticleType type;
  ParticleSide side;

  friend std::ostream& operator<< (std::ostream& out, const Particle& particle);
};


#endif
