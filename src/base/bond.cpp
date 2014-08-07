#include "bond.h"

Bond::Bond(const Particle& part1, const Particle& part2) : part1(part1), part2(part2) {
}

double Bond::distance() {
  return displacement().length();
}

Vector3D Bond::displacement() {
  return part1.pos - part2.pos;
}

double Bond::energyFENE(const Box& box, bool& bond_break) {
  Vector3D dr = box.pbcDisplacement(part1.pos, part2.pos);
  double r = dr.length();

  if (r >= r_max) {
    bond_break = 1;
    return 0;
  } else {
    double diff = r - r_equil;
    return -k/2 * r0*r0 * log(1.0 - diff*diff/(r0*r0));
  }
}

Vector3D Bond::forceFENE(const Box& box) {
  double force;
  Vector3D dr = box.pbcDisplacement(part1.pos, part2.pos);
  double r = dr.length();

  if (r >= r_max) {
    force = -force_max;
  } else {
    double diff = r - r_equil;
    force = -k * diff / (1.0 - diff*diff/(r0*r0));
  }

  return Vector3D(force*dr.x, force*dr.y, force*dr.z) / r;
}

std::ostream& operator<< (std::ostream& out, const Bond& bond) {
  out << "Particle 1: " << std::endl << bond.part1 << std::endl
      << "Particle 2: " << std::endl << bond.part2 << std::endl;
  return out;
}

