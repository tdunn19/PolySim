#include "particle.h"

const char* type_names[] = {
  "monomer", "solvent", "wall", "pore"
};

Particle::Particle() : index(0), type(solvent_type) {
  pos.zero();
  vel.zero();
  force.zero();
}

Particle::Particle(int index, ParticleType type)
    : index(index), type(type) {
  pos.zero();
  vel.zero();
  force.zero();
}

Particle::Particle(int index, double x, double y, double z)
    : index(index), pos(x, y, z), type(solvent_type) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, double x, double y, double z, ParticleType type)
    : index(index), pos(x, y, z), type(type) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, Vector3D pos, ParticleType type)
    : index(index), pos(pos), type(type) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, Vector3D pos, Vector3D vel, ParticleType type)
    : index(index), pos(pos), vel(vel), type(type) {
  force.zero();
}

Particle::Particle(int index, Vector3D pos, Vector3D vel, Vector3D force, ParticleType type)
    : index(index), pos(pos), vel(vel), force(force), type(type) {
}

Particle::Particle(const Particle& other) : type(other.type) {
  index = other.index;
  pos = other.pos;
  vel = other.vel;
  force = other.force;
}

std::ostream& operator<< (std::ostream& out, const Particle& part) {
  out << "Type: " << type_names[part.type] << std::endl
      << "Index: " << part.index << std::endl
      << "Position: " << part.pos << std::endl
      << "Velocity: " << part.vel << std::endl
      << "Force: " << part.force << std::endl;
  return out;
}

