#include "rng.cuh"
#include <iostream>
#include <cmath>
#include <cstdlib>

__device__ __host__ rng::rng(){
  m_s1 = 0;
  m_s2 = 0;
  m_s3 = 0;
  m_s4 = 0;

  m_gauss1 = 0;
  m_gauss2 = 0;
}

__device__ __host__ rng::rng(unsigned s1, unsigned s2, unsigned s3, unsigned s4) {

  m_s1 = s1;
  m_s2 = s2;
  m_s3 = s3;
  m_s4 = s4;

  m_gauss1 = 0;
  m_gauss2 = 0;

}

__device__ __host__ rng::rng(const rng &rng2){

  m_s1 = rng2.m_s1;
  m_s2 = rng2.m_s2;
  m_s3 = rng2.m_s3;
  m_s4 = rng2.m_s4;

  m_gauss1 = rng2.m_gauss1;
  m_gauss2 = rng2.m_gauss2;

}

__device__ __host__ rng::~rng() {}

__device__ __host__ unsigned rng::TauStep (unsigned &seed, int k1, int k2, int k3, unsigned M) {

  unsigned b = (((seed << k1)^seed)>>k2);
  seed = ((seed&M)<<k3)^b;
  return seed;

}

__device__ __host__ unsigned rng::LNG (unsigned &seed, unsigned a, unsigned b) {

  return seed = (a*seed + b);

}

__device__ __host__ double rng::hybrid() /*(unsigned s1, unsigned s2, unsigned s3, unsigned s4) */{

  return (2.3283064365387e-10*(TauStep(m_s1, 13, 19, 12, 4294967294UL) ^
  (TauStep(m_s2, 2, 25, 4, 4294967288UL) )^
  (TauStep(m_s3, 3, 11, 17, 4294967280UL))
  ^(LNG(m_s4, 1664525, 1013904223UL))));

}
__device__ __host__ double rng::Get_uniform() {

  return rng::hybrid();
}

__device__ __host__ double rng::Get_gauss() {

    double u = sqrt(-2*log(rng::Get_uniform()))*cos(2*M_PI*rng::Get_uniform());
    double v = sqrt(-2*log(rng::Get_uniform()))*sin(2*M_PI*rng::Get_uniform());

    return u;
};
