#include "gtest/gtest.h"
#include "../../src/base/particle.h"

TEST(ParticleTest, Construction) {
  Particle p1;
  Particle p2(42, 91.39, 0.3, -10.41);
  Particle p3(10, 4.2, -30.1, 40.029, monomer_type);
  Particle p4(3, Vector3D(77.3, 4.2, -45.0), pore_type);
  Particle p5(942, Vector3D(-7.1, -8.1, 0.3), Vector3D(0.24, -0.1, 3.9), pore_type);
  Particle p6(21, Vector3D(0.3, 44.19, 2.94), Vector3D(2.1, 0.2, 0.9),
              Vector3D(0.24, 4.1, -59.1), wall_type);
  Particle p7(p6);

  EXPECT_EQ(p1.index, 0);
  EXPECT_EQ(p2.index, 42);

  EXPECT_DOUBLE_EQ(p1.pos.y, 0.0);
  EXPECT_DOUBLE_EQ(p2.pos.z, -10.41);
  EXPECT_DOUBLE_EQ(p3.pos.z, 40.029);
  EXPECT_DOUBLE_EQ(p4.pos.x, 77.3);
  EXPECT_DOUBLE_EQ(p6.pos.y, 44.19);

  EXPECT_DOUBLE_EQ(p1.vel.z, 0.0);
  EXPECT_DOUBLE_EQ(p3.vel.x, 0.0);
  EXPECT_DOUBLE_EQ(p2.force.y, 0.0);
  EXPECT_DOUBLE_EQ(p5.vel.z, 3.9);
  EXPECT_DOUBLE_EQ(p6.force.y, 4.1);

  EXPECT_EQ(p1.type, solvent_type);
  EXPECT_EQ(p1.type, 1);
  EXPECT_EQ(p3.type, 0);
  EXPECT_EQ(p4.type, pore_type);
  EXPECT_EQ(p6.type, wall_type);

  EXPECT_TRUE(p6.index == p7.index &&
              p6.pos == p7.pos &&
              p6.vel == p7.vel &&
              p6.force == p7.force &&
              p6.type == p7.type);
}

