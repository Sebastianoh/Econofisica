#include "processo_stocastico.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

processo_stocastico::processo_stocastico() {
  m_p            = 0;
  m_E            = 0;
  dt             = 0.5;   //valore a caso
  sigma          = 0.5;   //valore a caso
  risk_free_rate = 0.02;
  m_n_steps      = 0;
}



processo_stocastico::processo_stocastico(double p, int n_steps, double E) {

  m_p            = p;
  m_E            = E;
  dt             = 0.5;   //valore a caso
  sigma          = 0.5;   //valore a caso
  risk_free_rate = 0.02;
  m_n_steps      = n_steps;
}
//destructor
processo_stocastico::~processo_stocastico() {
}

__device__ __host__ void processo_stocastico::eulero(double& S) {

  S = S*(1 + risk_free_rate*dt + sigma*sqrt(dt)*rng::Get_gauss());
}

__device__ __host__ void processo_stocastico::creazione_path(){

  for (size_t i = 0; i < m_n_steps; i++) {
    eulero(m_p);
  };
}

__device__ __host__ double processo_stocastico::Get_new_price() {
  creazione_path();
  return m_p;
}

  //payoff

__device__ __host__ double processo_stocastico::payoff() {

  return max((m_p - m_E), 0.);

}
