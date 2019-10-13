#ifndef __statistica_h__
#define __statistica_h__

#include "struct.h"

class statistica {

public:
  __device__ __host__ statistica(input_mc_data M) {};
  // __device__ __host__ statistica(double * array);

  __device__ __host__ double media (double * array);

private:
  // double * m_array;
  int m_size;
};

#endif
