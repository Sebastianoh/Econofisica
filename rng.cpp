#include "rng.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

rng::rng() {
  m_s1 = 0;
  m_s2 = 0;
  m_s3 = 0;
  m_s4 = 0;

}

rng::~rng() {}

void rng::first_generator() {

  srand(time(NULL));
  m_s1 = rand() % 1000000+128;
  m_s2 = rand() % 1000000+128;
  m_s3 = rand() % 1000000+128;
  m_s4 = rand() % 1000000+128;

}

__device__ double rng::TauStep (unsigned seed, int k1, int k2, int k3, unsigned M) {

  unsigned b = (((seed << k1)^seed)>>k2);
  seed = ((seed&M)<<k3)^b;
  return seed;

}

__device__ double rng::LNG     (unsigned seed, unsigned a, unsigned b) {

  return seed = (a*seed + b);

}

__device__ double rng::hybrid  (unsigned s1, unsigned s2, unsigned s3, unsigned s4) {

  return 2.3283064365387e-10 * ( TausStep(s1, 13, 19, 12, 4294967294UL) ^
  TausStep(s2, 2, 25, 4, 4294967288UL) ^ TausStep(s3, 3, 11, 17, 4294967280UL) ^
  LNG(s4, 1664525, 1013904223UL);

}

__global__ void rng:generator( double * r) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  r[i] = hybrid(m_s1, m_s2; m_s3; m_s4);

};
