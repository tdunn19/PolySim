#include "gtest/gtest.h"
#include "../src/util/vector3d.h"

TEST(Vector3DTest, Construction) {
  Vector3D v1;
  Vector3D v2(2.1, -3.8, 9.3);
  Vector3D v3(v2);

  EXPECT_EQ(v1.x, 0);
  EXPECT_EQ(v2.y, -3.8);
  EXPECT_EQ(v3.z, 9.3);
}
