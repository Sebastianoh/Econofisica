#ifndef __montecarlo_h__
#define __montecarlo_h__

#include "struct.h"
#include "processo_stocastico.h"

class montecarlo: public processo_stocastico {

public:
  __device__ __host__ montecarlo();
  __device__ __host__ montecarlo(input_mc_data mc, output_mc_data& output_mc);

  __device__ __host__ pricer_montercarlo()


}
