#include "gtest/gtest.h"
#include "../../src/base/polymer.h"

TEST(PolymerTest, Construction) {
  Polymer p1;
  Polymer p2(21);

  EXPECT_EQ(p1.num_monomers, 10);
  EXPECT_EQ(p2.num_monomers, 21);
}

TEST(PolymerTest, Functions) {
  Polymer p1;
  Polymer p2(21);

  p1.initialize(0);
  p2.initialize(25);
  
  EXPECT_EQ(p1.num_bonds, 9);
  EXPECT_EQ(p2.num_bonds, 20);
  EXPECT_EQ(p1.monomers[0].index, 0);
  EXPECT_EQ(p2.monomers[0].index, 25);
  EXPECT_EQ(p1.monomers[4].type, monomer_type);
  EXPECT_EQ(p2.monomers[20].type, monomer_type);
  EXPECT_EQ(p1.bonds[8].part1.index, 8);
  EXPECT_EQ(p2.bonds[3].part2.index, 29);
}

