#include "gtest/gtest.h"
#include "../src/util/vector3d.h"

TEST(Vector3DTest, Construction) {
  Vector3D v1;
  Vector3D v2(2.1, -3.8, 9.3);
  Vector3D v3(v2);

  EXPECT_DOUBLE_EQ(v1.x, 0);
  EXPECT_DOUBLE_EQ(v2.y, -3.8);
  EXPECT_DOUBLE_EQ(v3.z, 9.3);
}

TEST(Vector3DTest, Operators) {
  double a = 3.29;
  Vector3D v1(-9.2, 1.8, 15.93);
  Vector3D v2(4.193, 193.9, -1.31);
  Vector3D v3(21.3, 4.142, -0.301);
  Vector3D v4, v5;

  v5 = v1;
  EXPECT_DOUBLE_EQ(v5.x, v1.x);

  v4 = v1 + v3;
  EXPECT_DOUBLE_EQ(v4.z, 15.629);

  v4 = v1 - v2;
  EXPECT_DOUBLE_EQ(v4.y, -192.1);

  v4 = v3 * a;
  v5 = a * v3;
  EXPECT_DOUBLE_EQ(v4.y, 13.62718);
  EXPECT_DOUBLE_EQ(v5.z, -0.99029);
  EXPECT_DOUBLE_EQ(v4.x, v5.x);

  v4 = v2 / a;
  EXPECT_DOUBLE_EQ(v4.z, -0.3981762917933131);

  v3 += v1;
  EXPECT_DOUBLE_EQ(v3.x, 12.1);

  v3 -= v2;
  EXPECT_DOUBLE_EQ(v3.y, -187.958);

  v3 *= a;
  EXPECT_DOUBLE_EQ(v3.z, 55.72931);

  v3 /= a;
  EXPECT_DOUBLE_EQ(v3.x, 7.907);

  v4 *= a;
  EXPECT_TRUE(v2 == v4);
}

TEST(Vector3DTest, Functions) {
  Vector3D v1(0.31, 24.019, -6.0);
  Vector3D v2(1.21, -0.645, 8.19);
  Vector3D v3(4.1, 3.04, -7.48);

  v1.zero();
  EXPECT_DOUBLE_EQ(v1.length(), 0.0);
  EXPECT_DOUBLE_EQ(v2.lengthSquared(), 68.956225);
  EXPECT_DOUBLE_EQ(v1.dotProduct(v2), 0.0);
  EXPECT_DOUBLE_EQ(v3.dotProduct(v2), -58.261);

  v1 = v2.reverse();
  EXPECT_DOUBLE_EQ(v1.y, 0.645);
  EXPECT_DOUBLE_EQ(v1.lengthSquared(), 68.956225);

  v1 = v3.normalize();
  EXPECT_DOUBLE_EQ(v1.x, 0.45276373543156939);

  v1.zero();
  v1 = v1.normalize();
  EXPECT_DOUBLE_EQ(v1.z, 0.0);

  v1 = v2.crossProduct(v3);
  EXPECT_DOUBLE_EQ(v1.x, -20.073);
  EXPECT_DOUBLE_EQ(v1.y, 42.6298);
  EXPECT_DOUBLE_EQ(v1.z, 6.3229);
}
