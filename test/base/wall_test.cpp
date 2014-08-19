#include "gtest/gtest.h"
#include "../../src/base/wall.h"

TEST(WallTest, Construction) {
  Box b1(15.0, 15.0, 25.0);

  Wall w1(b1, 3, 3.0, 1);

  EXPECT_DOUBLE_EQ(w1.box.length.z, 25.0);
  EXPECT_EQ(w1.num_layers, 3);
  EXPECT_DOUBLE_EQ(w1.density, 3.0);
  EXPECT_DOUBLE_EQ(w1.wall_spacing.z, 0.69336127435063477);
  EXPECT_DOUBLE_EQ(w1.pore_length, 1.3867225487012695);

  Wall w2(b1, 5, 1.0, 0);

  EXPECT_DOUBLE_EQ(w2.wall_spacing.x, 1.0);
  EXPECT_FALSE(w2.has_pore);
}

TEST(WallTest, Initialize) {
  Box b1(12.7, 9.6, 16.6);
  Wall w1(b1, 3, 3.0, 1);
  w1.initialize(0);

  EXPECT_EQ(w1.num_particles_1d.x, 18);
  EXPECT_EQ(w1.num_particles_1d.y, 14);
  EXPECT_EQ(w1.num_particles, 756 - 3);
  EXPECT_DOUBLE_EQ(w1.wall_spacing.x, 0.70555555555555549);
  EXPECT_DOUBLE_EQ(w1.wall_spacing.y, 0.68571428571428572);
  EXPECT_TRUE(w1.has_pore);
  EXPECT_EQ(w1.pore_imin.x, 8);
  EXPECT_EQ(w1.pore_imin.y, 6);
  EXPECT_EQ(w1.pore_imax.x, 10);
  EXPECT_EQ(w1.pore_imax.y, 8);
  EXPECT_DOUBLE_EQ(w1.pore_min.x, 5.6444444444444439);
  EXPECT_DOUBLE_EQ(w1.pore_min.y, 4.1142857142857138);
  EXPECT_DOUBLE_EQ(w1.pore_min.z, 7.6066387256493657);
  EXPECT_DOUBLE_EQ(w1.pore_max.x, 7.0555555555555549);
  EXPECT_DOUBLE_EQ(w1.pore_max.y, 5.4857142857142858);
  EXPECT_DOUBLE_EQ(w1.pore_max.z, 8.9933612743506366);
  EXPECT_DOUBLE_EQ(w1.pore_centre.x, 6.3499999999999996);
  EXPECT_DOUBLE_EQ(w1.pore_centre.z, 8.3);
  EXPECT_EQ(w1.particles.size(), w1.num_particles);

  for (Particle::Iterator part = w1.particles.begin(); part != w1.particles.end(); ++part) {
    if (part->pos.z > w1.pore_min.z && part->pos.z < w1.pore_max.z) {
      if (part->type == wall_type) {
        EXPECT_TRUE((part->pos.x <= w1.pore_min.x || part->pos.x >= w1.pore_max.x) ||
                    (part->pos.y <= w1.pore_min.y || part->pos.y >= w1.pore_max.y));
      } else {
        EXPECT_TRUE(part->type == pore_type);
        EXPECT_TRUE((part->pos.x >= w1.pore_min.x && part->pos.x <= w1.pore_max.x) &&
                    (part->pos.y >= w1.pore_min.y && part->pos.y <= w1.pore_max.y));
      }
    } else {
      EXPECT_TRUE(part->type == wall_type);
    }
  }

  Box b2(3.6, 3.6, 10.6);
  Wall w2(b2, 2, 6.0, 2);
  w2.initialize(0);

  EXPECT_DOUBLE_EQ(w2.pore_length, 0.55032120814910446);
  EXPECT_DOUBLE_EQ(w2.pore_min.z, 5.0248393959254471);
  EXPECT_DOUBLE_EQ(w2.pore_max.z, 5.5751606040745525);
  EXPECT_DOUBLE_EQ(w2.pore_centre.z, 5.3);
  EXPECT_EQ(w2.particles.size(), w2.num_particles);

  for (Particle::Iterator part = w2.particles.begin(); part != w2.particles.end(); ++part) {
    if (part->pos.z > w2.pore_min.z && part->pos.z < w1.pore_max.z) {
      if (part->type == wall_type) {
        EXPECT_TRUE((part->pos.x <= w1.pore_min.x || part->pos.x >= w1.pore_max.x) ||
                    (part->pos.y <= w1.pore_min.y || part->pos.y >= w1.pore_max.y));
      } else {
        EXPECT_TRUE(part->type == pore_type);
        EXPECT_TRUE((part->pos.x >= w1.pore_min.x && part->pos.x <= w1.pore_max.x) &&
                    (part->pos.y >= w1.pore_min.y && part->pos.y <= w1.pore_max.y));
      }
    } else {
      EXPECT_TRUE(part->type == wall_type);
    }
  }
}

TEST(WallTest, PlacePolymer) {
  Polymer p1(21);
  p1.initialize(0);

  Box b1(14.5, 14.5, 20.0);
  Wall w1(b1, 3, 3.0, 1);
  w1.initialize(p1.num_monomers);

  w1.placePolymer(p1);

  EXPECT_EQ(p1.monomers[10].index, 10);
  EXPECT_EQ(p1.monomers[20].index, 20);
  EXPECT_EQ(w1.particles[0].index, 21);
  EXPECT_DOUBLE_EQ(p1.monomers[10].pos.x, w1.pore_centre.x);
  EXPECT_EQ(p1.monomers[10].side, pore);
}
