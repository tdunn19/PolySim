#include "wall.h"
#include "particle.h"

Wall::Wall(Box& box, int num_layers, double density, int pore_width)
  : box(box), num_layers(num_layers), density(density), pore_width(pore_width) {
  wall_spacing = pow(density, -1.0/3.0);
  pore_length = (num_layers - 1) * wall_spacing.z;
  if (pore_width > 0) {
    has_pore = true;
  } else {
    has_pore = false;
  }
}

void Wall::initialize(int index) {
  num_particles_1d.x = static_cast<int> (box.length.x/wall_spacing.x + 0.5);
  num_particles_1d.y = static_cast<int> (box.length.y/wall_spacing.y + 0.5);
  num_particles = num_particles_1d.x * num_particles_1d.y * num_layers;
  wall_spacing.x = box.length.x / num_particles_1d.x;
  wall_spacing.y = box.length.y / num_particles_1d.y;

  if (has_pore) {
    // Identify the lattice points that bound the pore.
    pore_imin.x = static_cast<int>(num_particles_1d.x / 2.0) - 1;
    pore_imin.y = static_cast<int>(num_particles_1d.y / 2.0) - 1;
    pore_imin.z = 0;
    pore_imax.x = static_cast<int>(num_particles_1d.x / 2.0) + pore_width;
    pore_imax.y = static_cast<int>(num_particles_1d.y / 2.0) + pore_width;
    pore_imax.z = num_layers - 1;

    pore_min.x = pore_imin.x * wall_spacing.x;
    pore_min.y = pore_imin.y * wall_spacing.y;
    pore_min.z = pore_imin.z * wall_spacing.z + box.half_length.z - pore_length/2.0;
    pore_max.x = pore_imax.x * wall_spacing.x;
    pore_max.y = pore_imax.y * wall_spacing.y;
    pore_max.z = pore_imax.z * wall_spacing.z + box.half_length.z - pore_length/2.0;

    pore_centre = (pore_min + pore_max) / 2.0;

    num_particles -= pore_width * pore_width * num_layers;
  }

  for (int i = 0; i < num_particles_1d.x; ++i) {
    for (int j = 0; j < num_particles_1d.y; ++j) {
      for (int k = 0; k < num_layers; ++k) {
        if (has_pore) {
          if ((i > pore_imin.x && i < pore_imax.x) &&
              (j > pore_imin.y && j < pore_imax.y)) {
            // This lattice point is part of the pore channel.
            break;
          }

          if ((i >= pore_imin.x && i <= pore_imax.x) &&
              (j >= pore_imin.y && j <= pore_imax.y) &&
              (k > pore_imin.z  && k <  pore_imax.z)) {
            // This lattice point is part of the pore wall.
            particles.push_back(Particle(index, i*wall_spacing.x, j*wall_spacing.y,
                                         pore_min.z + k*wall_spacing.z, pore_type));
            ++index;
            continue;
          }
        }
        particles.push_back(Particle(index, i*wall_spacing.x, j*wall_spacing.y,
                                     box.half_length.z - pore_length/2.0 + k*wall_spacing.z,
                                     wall_type));
        ++index;
      }
    }
  }
}

void Wall::placePolymer(Polymer& polymer) {
  if (has_pore) {
    if (polymer.num_monomers % 2 == 0) {
      polymer.monomers[polymer.num_monomers/2].pos = pore_centre;
    } else {
      // Place middle monomer in the centre of the pore.
      polymer.monomers[polymer.num_monomers/2].pos = pore_centre;
      polymer.monomers[polymer.num_monomers/2].updateSide(*this);
      //polymer.monomers[polymer.num_monomers/2].side = pore;
    }
  } 
}

std::ostream& operator<< (std::ostream& out, const Wall& wall) {
  out << "Number of layers: " << wall.num_layers << std::endl
      << "Number of particles: " << wall.num_particles << std::endl;
  return out;
}

