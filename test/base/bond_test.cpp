#include "gtest/gtest.h"
#include "../../src/base/bond.h"

TEST(BondTest, Construction) {
  Particle p1;
  Particle p2(21, Vector3D(0.3, 44.19, 2.94), Vector3D(2.1, 0.2, 0.9),
              Vector3D(0.24, 4.1, -59.1), wall_type);

  Bond b1(p1, p2);

  EXPECT_EQ(b1.part1.index, 0);
  EXPECT_EQ(b1.part2.type, wall_type);
  EXPECT_DOUBLE_EQ(b1.part2.force.y, 4.1);
}

TEST(BondTest, Functions) {
  Particle p1(3, Vector3D(77.3, 4.2, -45.0), pore_type);
  Particle p2(942, Vector3D(-7.1, -8.1, 0.3), Vector3D(0.24, -0.1, 3.9), pore_type);
  Particle p3(21, Vector3D(0.3, 44.19, 2.94), Vector3D(2.1, 0.2, 0.9),
              Vector3D(0.24, 4.1, -59.1), wall_type);

  Bond b1(p1, p2);
  Bond b2(p1, p3);

  EXPECT_DOUBLE_EQ(b1.displacement().x, 84.4);
  EXPECT_DOUBLE_EQ(b2.distance(), 99.128420243641528);

  Box box(10.0, 10.0, 15.0);
  bool bond_break = 0;

  Bond b3(Particle(1, Vector3D(5.2, 0.4, 12.1), monomer_type),
          Particle(2, Vector3D(9.5, 4.2, 0.5), monomer_type));
  Bond b4(Particle(3, Vector3D(9.9, 0.0, 0.0), monomer_type),
          Particle(4, Vector3D(0.1, 0.0, 0.0), monomer_type));

  EXPECT_DOUBLE_EQ(b3.forceFENE(box).length(), 100.0);
  EXPECT_DOUBLE_EQ(b3.energyFENE(box, bond_break), 0.0);
  EXPECT_TRUE(bond_break);
  bond_break = 0;

  EXPECT_DOUBLE_EQ(b4.forceFENE(box).length(), 23.472222222222261);
  EXPECT_DOUBLE_EQ(b4.forceFENE(box).x, -23.472222222222261);
  EXPECT_DOUBLE_EQ(b4.forceFENE(box).y, 0.0);

  std::cout << b3 << std::endl;
}

