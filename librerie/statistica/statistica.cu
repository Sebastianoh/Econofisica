#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "statistica.h"


//si è reso necessario introdurre variabile n_step_simulazione poiché
// usando il numero fixed di simulazioni quando avevo 1 solo numero,
// la media e dev_std venivano calcolate comunque con n = n_sim massimo


// a questo punto il numero fissato di simulazioni diventa una variabile
//  inutile quindi la cancello

__device__ __host__ statistica::statistica() {

  m_somma_payoff        = 0;
  m_somma_quadra_payoff = 0;
  m_deviazione_standard = 0;
  m_step_simulazione    = 0;
  // m_num_simulazioni     = 1;

}


__device__ __host__ void statistica::analisi(double payoff) {

  ++ m_step_simulazione ;

  m_somma_payoff        += payoff;
  m_somma_quadra_payoff += pow(payoff,2);
  m_deviazione_standard += pow(payoff - (m_somma_payoff/m_step_simulazione), 2);

}


__device__ __host__ double statistica::get_somma_payoff() {
  return m_somma_payoff;
}

__device__ __host__ double statistica::get_somma_quadra_payoff() {
  return m_somma_quadra_payoff;
}


__device__ __host__ double statistica::get_media() {
  return m_somma_payoff/m_step_simulazione;
}

__device__ __host__ double statistica::get_deviazione_standard() {
  return sqrt(m_deviazione_standard/m_step_simulazione);
}
