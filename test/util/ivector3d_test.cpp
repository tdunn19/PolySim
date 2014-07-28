#include "gtest/gtest.h"
#include "../../src/util/ivector3d.h"

TEST(IVector3DTest, Construction) {
  IVector3D v1;
  IVector3D v2(2, -3, 9);
  IVector3D v3(v2);

  EXPECT_EQ(v1.x, 0);
  EXPECT_EQ(v2.y, -3);
  EXPECT_EQ(v3.z, 9);
  EXPECT_TRUE(v2 == v3);
}

TEST(IVector3DTest, Operators) {
  int a = 3;
  IVector3D v1(-9, 1, 16);
  IVector3D v2(4, 193, -1);
  IVector3D v3(21, 4, 0);
  IVector3D v4, v5;

  v5 = v1;
  EXPECT_EQ(v5.x, v1.x);

  v4 = v1 + v3;
  EXPECT_EQ(v4.z, 16);

  v4 = v1 - v2;
  EXPECT_EQ(v4.y, -192);

  v4 = v3 * a;
  v5 = a * v3;
  EXPECT_EQ(v4.y, 12);
  EXPECT_EQ(v5.z, 0);
  EXPECT_EQ(v4.x, v5.x);
  EXPECT_TRUE(v4 == v5);

  v3 += v1;
  EXPECT_EQ(v3.x, 12);

  v3 -= v2;
  EXPECT_EQ(v3.y, -188);

  v3 *= a;
  EXPECT_EQ(v3.z, 51);
}

TEST(IVector3DTest, Functions) {
  IVector3D v1(0, 24, -6);
  IVector3D v2(1, -1, 8);
  IVector3D v3(4, 3, -7);

  v1.zero();
  EXPECT_EQ(v1.length(), 0.0);
  EXPECT_DOUBLE_EQ(v2.lengthSquared(), 66.0);

  v1 = v2.reverse();
  EXPECT_EQ(v1.y, 1);
  EXPECT_DOUBLE_EQ(v1.lengthSquared(), 66.0);
}
