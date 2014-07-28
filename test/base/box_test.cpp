#include "gtest/gtest.h"
#include "../../src/base/box.h"

TEST(BoxTest, Construction) {
  Box b1;
  Box b2(2.10, 0.14, 9.6);
  Vector3D v3(0.4, 3.21, 1.5);
  Box b3(v3);

  EXPECT_DOUBLE_EQ(b1.length.y, 0.0);
  EXPECT_DOUBLE_EQ(b2.length.x, 2.10);
  EXPECT_DOUBLE_EQ(b3.length.z, 1.5);

  EXPECT_DOUBLE_EQ(b1.half_length.x, 0.0);
  EXPECT_DOUBLE_EQ(b2.half_length.z, 4.8);
  EXPECT_DOUBLE_EQ(b3.half_length.x, 0.2);

  EXPECT_DOUBLE_EQ(b1.volume, 0.0);
  EXPECT_DOUBLE_EQ(b2.volume, 2.8224);
  EXPECT_DOUBLE_EQ(b3.volume, 1.926);
}

TEST(BoxTest, Functions) {
  Box b1(5.0, 5.0, 10.0);
  Vector3D v1(4.5, 4.0, 9.4);
  Vector3D v2(0.2, 1.1, 0.6);
  Vector3D v3(5.3, -3.9, 12.0);
  Vector3D v4, v5;
  Random r1;
  int num_samples = 1000;

  EXPECT_DOUBLE_EQ(b1.distance(v1, v2), sqrt(0.7*0.7 + 2.1*2.1 + 1.2*1.2));

  b1.pbcPosition(v3);
  EXPECT_DOUBLE_EQ(v3.x, 0.3);
  EXPECT_DOUBLE_EQ(v3.y, 1.1);
  EXPECT_DOUBLE_EQ(v3.z, 2.0);

  for (int i = 0; i < num_samples; ++i) {
    v4 = b1.randomPoint(r1);
    EXPECT_TRUE((v4.x > 0 && v4.x < b1.length.x) &&
                (v4.y > 0 && v4.y < b1.length.y) &&
                (v4.z > 0 && v4.z < b1.length.z));

    v5 = b1.randomPoint(r1);
    EXPECT_FALSE(v4 == v5);
  }
}
