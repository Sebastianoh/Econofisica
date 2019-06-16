#include "rng.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

rng::rng(){}

rng::rng(unsigned s1, unsigned s2, unsigned s3, unsigned s4) {
  m_s1 = s1;
  m_s2 = s2;
  m_s3 = s3;
  m_s4 = s4;

}

rng::~rng() {}

/*void rng::first_generator() {

  srand(time(NULL));
  m_s1 = rand() % 1000000+128;
  m_s2 = rand() % 1000000+128;
  m_s3 = rand() % 1000000+128;
  m_s4 = rand() % 1000000+128;

}*/

__device__ unsigned rng::TauStep (unsigned seed, int k1, int k2, int k3, unsigned M) {

  unsigned b = (((seed << k1)^seed)>>k2);
  seed = ((seed&M)<<k3)^b;
  return seed;

}

__device__ unsigned rng::LNG (unsigned seed, unsigned a, unsigned b) {

  return seed = (a*seed + b);

}

__device__ unsigned rng::hybrid() /*(unsigned s1, unsigned s2, unsigned s3, unsigned s4) */{

  return (2.3283064365387e-10*(TauStep(m_s1, 13, 19, 12, 4294967294UL) ^
  (TauStep(m_s2, 2, 25, 4, 4294967288UL) )^
  (TauStep(m_s3, 3, 11, 17, 4294967280UL))
  ^(LNG(m_s4, 1664525, 1013904223UL))));

}

/*__global__ void rng::combined_generator(unsigned * r) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  r[i] = hybrid(m_s1, m_s2, m_s3, m_s4);

}
*/
