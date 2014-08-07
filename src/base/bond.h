#ifndef BOND_H
#define BOND_H

#include <cmath>

#include "particle.h"
#include "box.h"
#include "../util/vector3d.h"

class Bond {
 public:
  Bond(const Particle& part1, const Particle& part2);

  double distance();
  Vector3D displacement();
  double energyFENE(const Box& box, bool& bond_break);
  Vector3D forceFENE(const Box& box);

  const Particle& part1, part2;

  friend std::ostream& operator<< (std::ostream& out, const Bond& bond);

 private:
  static constexpr double r_max = 2.0;
  static constexpr double force_max = 100.0;
  static constexpr double r_equil = 0.7;
  static constexpr double k = 40.0;
  static constexpr double r0 = r_max - r_equil;
};

#endif
