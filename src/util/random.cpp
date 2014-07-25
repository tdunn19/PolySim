#include "random.h"

Random::Random() : seed_(time(NULL) + getpid()) {
  generator_.seed(seed_);
}

Random::Random(unsigned long seed) : seed_(seed) {
  generator_.seed(seed_);
}

Random::~Random() {
}

void Random::setSeed(unsigned long seed) {
  seed_ = seed;
}

unsigned long Random::getSeed() {
  return seed_;
}

int Random::uniformInt(int min, int max) {
  if (min > max) {
    std::swap(min, max);
  }
  UniformIntDistribution dist(min, max);
  return dist(generator_);
}

double Random::uniformReal() {
  UniformRealDistribution dist;
  return dist(generator_);
}

double Random::uniformReal(double min, double max) {
  UniformRealDistribution dist(min, max);
  return dist(generator_);
}

Vector3D Random::randomVector() {
  return Vector3D(uniformReal(),
                  uniformReal(),
                  uniformReal());
}

Vector3D Random::randomVector(Vector3D min, Vector3D max) {
  return Vector3D(uniformReal(min.x, max.x),
                  uniformReal(min.y, max.y),
                  uniformReal(min.z, max.z));
}

IVector3D Random::randomIVector(IVector3D min, IVector3D max) {
  return IVector3D(uniformInt(min.x, max.x),
                   uniformInt(min.y, max.y),
                   uniformInt(min.z, max.z));
}

bool Random::metropolis(double ratio) {
  if (ratio > 1.0) {
    return true;
  } else {
    double ran = uniformReal();
    if (ran < ratio) {
      return true;
    } else {
      return false;
    }
  }
}
