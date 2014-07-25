#include <vector>

#include "gtest/gtest.h"
#include "../src/util/random.h"

TEST(RandomTest, Construction) {
  Random r1;
  EXPECT_EQ(r1.getSeed(), time(NULL) + getpid());

  Random r2(4720274);
  EXPECT_EQ(r2.getSeed(), 4720274);
  r2.setSeed(394830);
  EXPECT_EQ(r2.getSeed(), 394830);
}

TEST(RandomTest, UniformReal) {
  Random r1;
  int num_samples = 10000;
  double x, sum, mean, stdev;

  for (int i = 0; i < num_samples; ++i) {
    x = r1.uniformReal();
    EXPECT_TRUE(x > 0 && x < 1);
    sum += x;
  }
  sum /= num_samples;

  mean = 0.5;
  stdev = sqrt(1.0/12.0);
  EXPECT_TRUE(sum > (mean - stdev) && sum < (mean + stdev));

  sum = 0;
  for (int i = 0; i < num_samples; ++i) {
    x = r1.uniformReal(4.5, 17.1);
    EXPECT_TRUE(x > 4.5 && x < 17.1);
    sum += x;
  }
  sum /= num_samples;

  mean = (17.1 + 4.5) / 2.0;
  stdev = (17.1 - 4.5) / sqrt(12.0);
  EXPECT_TRUE(sum > (mean - stdev) && sum < (mean + stdev));
}

TEST(RandomTest, UniformInt) {
  Random r1;
  int num_samples = 10000;
  int x;
  double sum, mean, stdev;

  for (int i = 0; i < num_samples; ++i) {
    x = r1.uniformInt(-39, 91);
    EXPECT_TRUE(x > -40 && x < 92);
    sum += x;
  }
  sum /= num_samples;

  mean = (91 - 39) / 2.0;
  stdev = sqrt((pow(91 + 39 + 1, 2) - 1) / 12.0);
  EXPECT_TRUE(sum > (mean - stdev) && sum < (mean + stdev));
}

TEST(RandomTest, RandomVector) {
  Random r1;
  Vector3D v1, v2;
  Vector3D min(-29.1, 1.2, -8.2);
  Vector3D max(0.3, 4.8, 56.1);
  int num_samples = 1000;

  for (int i = 0; i < num_samples; ++i) {
    v1 = r1.randomVector();
    EXPECT_TRUE((v1.x > 0 && v1.x < 1) &&
                (v1.y > 0 && v1.y < 1) &&
                (v1.z > 0 && v1.z < 1));

    v2 = r1.randomVector(min, max);
    EXPECT_TRUE((v2.x > min.x && v2.x < max.x) &&
                (v2.y > min.y && v2.y < max.y) &&
                (v2.z > min.z && v2.z < max.z));
  }
}

TEST(RandomTest, Determinism) {
  Random r1(39520);
  Random r2(39520);
  double x, y;
  int j, k;

  for (int i = 0; i < 10; ++i) {
    x = r1.uniformReal(); 
    y = r2.uniformReal();
    j = r1.uniformInt(0, 5000);
    k = r2.uniformInt(0, 5000);
    EXPECT_DOUBLE_EQ(x, y);
    EXPECT_EQ(j, k);
  }

  Random r3, r4;

  for (int i = 0; i < 10; ++i) {
    x = r3.uniformReal(); 
    y = r4.uniformReal();
    j = r3.uniformInt(0, 5000);
    k = r4.uniformInt(0, 5000);
    EXPECT_DOUBLE_EQ(x, y);
    EXPECT_EQ(j, k);
  }
}

TEST(RandomTest, Uniqueness) {
  Random r1;
  Random r2(3018);
  int num_samples = 1000;
  std::vector<double> doubles;
  std::vector<int> ints;
  std::vector<double>::iterator doubles_iter;
  std::vector<int>::iterator ints_iter;

  for (int i = 0; i < num_samples; ++i) {
    doubles.push_back(r1.uniformReal());
  }
  EXPECT_EQ(doubles.size(), num_samples);
  doubles_iter = std::unique(doubles.begin(), doubles.end());
  doubles.resize(std::distance(doubles.begin(), doubles_iter));
  EXPECT_EQ(doubles.size(), num_samples);

  for (int i = 0; i < num_samples; ++i) {
    ints.push_back(r2.uniformInt(-394710, 8810297));
  }
  EXPECT_EQ(ints.size(), num_samples);
  ints_iter = std::unique(ints.begin(), ints.end());
  ints.resize(std::distance(ints.begin(), ints_iter));
  EXPECT_EQ(ints.size(), num_samples);
}

