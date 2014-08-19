#include "particle.h"
#include "wall.h"

const char* type_names[] = {
  "monomer", "solvent", "wall", "pore"
};

Particle::Particle() : index(0), type(solvent_type), side(none) {
  pos.zero();
  vel.zero();
  force.zero();
}

Particle::Particle(int index, ParticleType type)
    : index(index), type(type), side(none) {
  pos.zero();
  vel.zero();
  force.zero();
}

Particle::Particle(int index, double x, double y, double z)
    : index(index), pos(x, y, z), type(solvent_type), side(none) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, double x, double y, double z, ParticleType type)
    : index(index), pos(x, y, z), type(type), side(none) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, Vector3D pos, ParticleType type)
    : index(index), pos(pos), type(type), side(none) {
  vel.zero();
  force.zero();
}

Particle::Particle(int index, Vector3D pos, Vector3D vel, ParticleType type)
    : index(index), pos(pos), vel(vel), type(type), side(none) {
  force.zero();
}

Particle::Particle(int index, Vector3D pos, Vector3D vel, Vector3D force, ParticleType type)
    : index(index), pos(pos), vel(vel), force(force), type(type), side(none) {
}

Particle::Particle(const Particle& other) : type(other.type), side(other.side) {
  index = other.index;
  pos = other.pos;
  vel = other.vel;
  force = other.force;
}

void Particle::updateSide(const Wall& wall) {
  if (isInPore(wall)) {
    side = pore; 
  } else if (side != cis && side != trans) {
    // Particle was in pore, but has exited.
    if (isInWall(wall)) {
      side = pore;
    } else if (pos.z < wall.pore_min.z) {
      side = cis;
    } else if (pos.z > wall.pore_max.z) {
      side = trans;
    }
  }
}

bool Particle::isInPore(const Wall& wall) {
  if (wall.has_pore == false) {
    return false;
  }

  if (pos.x > wall.pore_min.x && pos.x < wall.pore_max.x) {
    if (pos.y > wall.pore_min.y && pos.y < wall.pore_max.y) {
      if (pos.z > wall.pore_min.z && pos.z < wall.pore_max.z) {
        return true;
      }
    }
  }

  return false;
}

bool Particle::isInWall(const Wall& wall) {
  if (isInPore(wall)) {
    return false;
  } else if (pos.z > wall.pore_min.z && pos.z < wall.pore_max.z) {
    return true;
  } else {
    return false;
  }
}

std::ostream& operator<< (std::ostream& out, const Particle& part) {
  out << "Type: " << type_names[part.type] << std::endl
      << "Index: " << part.index << std::endl
      << "Position: " << part.pos << std::endl
      << "Velocity: " << part.vel << std::endl
      << "Force: " << part.force << std::endl;
  return out;
}

