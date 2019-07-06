#include <iostream>
#include <cmath>
#include <cstdlib>
#include "montecarlo.h"

__device__ __host__ montecarlo::montecarlo(){}

__device__ __host__ montecarlo::montecarlo(input_mc_data mc)/*, output_mc_data& output_mc)*/ {

  m_N_simulazioni = mc.N_simulazioni;
  m_N_tb = mc.N_tb; //n thread per blocco
  m_N_b = mc.N_b;   //numero blocchi

}

__device__ __host__ void montecarlo::pricer_montercarlo(double* (&array)) {
  // for (size_t i = 0; i < m_N_simulazioni; i++) {
    // array[i] = processo_stocastico::creazione_path();
  // }
}
