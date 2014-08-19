#include "gtest/gtest.h"
#include "../../src/base/particle.h"
#include "../../src/base/box.h"
#include "../../src/base/wall.h"

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

  p3.side = cis;
  EXPECT_EQ(p3.side, cis);
  p4.side = pore;
  EXPECT_EQ(p4.side, pore);
  p5.side = trans;
  EXPECT_EQ(p5.side, trans);
}

TEST(ParticleTest, Functions) {
  Box b1(12.7, 9.6, 16.6);
  Wall w1(b1, 3, 3.0, 1);
  w1.initialize(0);
  
  Particle p1(w1.num_particles, monomer_type);
  Particle p2(p1.index+1, 5.65, 0.3, -0.5);
  Particle p3(p2.index+1, 7.0, 5.23, 15.8, monomer_type);
  Particle p4(p3.index+1, Vector3D(6.95, 5.47, 7.607), pore_type);
  Particle p5(p4.index+1, Vector3D(12.5, 1.2, 8.3), Vector3D(0.24, -0.1, 3.9), pore_type);

  EXPECT_FALSE(p1.isInPore(w1) || p1.isInWall(w1));
  EXPECT_FALSE(p2.isInPore(w1) || p2.isInWall(w1));
  EXPECT_FALSE(p3.isInPore(w1) || p3.isInWall(w1));
  EXPECT_TRUE(p4.isInPore(w1) && !p4.isInWall(w1));
  EXPECT_TRUE(!p5.isInPore(w1) && p5.isInWall(w1));
  EXPECT_EQ(w1.particles[w1.num_particles-1].index, 752);
  EXPECT_EQ(p1.index, 753);

  p1.updateSide(w1);
  EXPECT_EQ(p1.side, 0);
  p2.updateSide(w1);
  EXPECT_EQ(p2.side, cis);
  p3.updateSide(w1);
  EXPECT_EQ(p3.side, trans);
  p4.updateSide(w1);
  EXPECT_EQ(p4.side, pore);
  p4.pos.z -= 0.1;
  p4.updateSide(w1);
  EXPECT_EQ(p4.side, cis);
  p5.updateSide(w1);
  EXPECT_EQ(p5.side, pore);
  p5.pos.z += 0.7;
  p5.updateSide(w1);
  EXPECT_EQ(p5.side, trans);

  std::vector<Particle> particles;
  particles.push_back(p1);
  particles.push_back(p2);
  particles.push_back(p3);
  particles.push_back(p4);
  particles.push_back(p5);

  Wall w2(b1, 1, 3.0, 0);
  w2.initialize(p5.index+1);

  for (Particle::Iterator part = particles.begin(); part != particles.end(); ++part) {
    EXPECT_FALSE(part->isInPore(w2) || part->isInWall(w2));
    part->updateSide(w2);
    EXPECT_TRUE(part->side == cis || part->side == trans);
  }
}

