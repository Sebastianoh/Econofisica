#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "statistica.h"

__device__ __host__ statistica::statistica(input_mc_data M) {

   m_somma_payoff        = 0;
   m_somma_quadra_payoff = 0;
   m_deviazione_standard = 0;
   m_num_simulazioni     = M.N_simulazioni;
}

__device__ __host__ void statistica::analisi(double payoff) {

  m_somma_payoff        += payoff;
  m_somma_quadra_payoff += pow(payoff,2);
  m_deviazione_standard += pow(payoff - m_media, 2);
}


__device__ __host__ double statistica::get_somma_payoff() {
  return m_somma_payoff;
}

__device__ __host__ double statistica::get_somma_quadra_payoff() {
  return m_somma_quadra_payoff;
}


__device__ __host__ double statistica::get_media() {
  return m_somma_payoff/m_num_simulazioni;
}

__device__ __host__ double statistica::get_deviazione_standard() {
  return sqrt(m_deviazione_standard/m_num_simulazioni);
}
