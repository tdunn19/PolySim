#include "polymer.h"

Polymer::Polymer() : num_monomers(10) {
}

Polymer::Polymer(int num_monomers) : num_monomers(num_monomers) {
}

void Polymer::initialize(int index) {
  for (int i = 0; i < num_monomers; ++i) {
    monomers.push_back(Particle(index+i, monomer_type));
  }

  for (int i = 0; i < num_monomers-1; ++i) {
    bonds.push_back(Bond(monomers[i], monomers[i+1]));
    num_bonds++;
  }
}


std::ostream& operator<< (std::ostream& out, const Polymer& polymer) {
  out << "Number of monomers: " << polymer.num_monomers << std::endl
      << "Number of bonds: " << polymer.num_bonds << std::endl;
  return out;
}

