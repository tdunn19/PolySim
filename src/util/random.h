#ifndef RANDOM_H
#define RANDOM_H

#include <cmath>
#include <ctime>
#include <random>
#include <unistd.h>

#include "vector3d.h"
#include "ivector3d.h"


class Random {
 public:
  typedef std::mt19937 RandomNumberGenerator;
  typedef std::uniform_int_distribution<int> UniformIntDistribution;
  typedef std::uniform_real_distribution<double> UniformRealDistribution;

  Random();
  Random(unsigned long seed);
  ~Random();

  void setSeed(unsigned long seed);
  unsigned long getSeed();
  int uniformInt(int min, int max);
  double uniformReal();
  double uniformReal(double min, double max);
  Vector3D randomVector();
  Vector3D randomVector(Vector3D min, Vector3D max);
  IVector3D randomIVector(IVector3D min, IVector3D max);
  bool metropolis(double ratio);

 private:
  unsigned long seed_;
  RandomNumberGenerator generator_;
};

#endif // RANDOM_H
/*
  virtual ~Random();

  Vector3D randPoint(Vector3D min, Vector3D max);
  bool metropolis(double ratio);

*/
