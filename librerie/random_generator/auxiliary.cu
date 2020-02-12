#include <cmath>
#include <cstdlib>
#include <iostream>
#include "auxiliary.h"

using namespace std;

__device__ __host__ auxiliary::auxiliary() {

  _seed = 130;

}

__device__ __host__ auxiliary::auxiliary(const unsigned int seed) {

  _seed = seed;

}

__device__ __host__ unsigned auxiliary::Tau() {

  int k1 = 13;
  int k2 = 25;
  int k3 = 11;

  unsigned M = 4294967294UL;

  unsigned int z = _seed;

  unsigned b = (((z << k1) ^z) >> k2);

  _seed = ((z & M) << k3) ^b;

  return _seed;

}

__device__ __host__ unsigned auxiliary::Get_unsigned_int() {

  return Tau();

}
