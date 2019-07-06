#ifndef __montecarlo_h__
#define __montecarlo_h__

#include "struct.h"

class montecarlo{

public:
  __device__ __host__ montecarlo();
  __device__ __host__ montecarlo(input_mc_data mc);/*, output_mc_data& output_mc)*/

  __device__ __host__ void pricer_montercarlo(double *(&array));

private:

  int m_N_simulazioni, m_N_tb, m_N_b;

};

#endif
