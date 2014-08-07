#ifndef POLYMER_H
#define POLYMER_H

#include <cmath>
#include <vector>

#include "particle.h"
#include "bond.h"
#include "../util/vector3d.h"

class Polymer {
 public:
  Polymer();
  Polymer(int num_monomers);

  void initialize(int index);

  friend std::ostream& operator<< (std::ostream& out, const Polymer& polymer);

  std::vector<Particle> monomers;
  std::vector<Bond> bonds;
  int num_monomers;
  int num_bonds;
};


#endif
