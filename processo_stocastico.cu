#include <iostream>
#include <cmath>
#include <cstdlib>
#include "processo_stocastico.h"
#include "rng.h"

__device__ __host__ processo_stocastico::processo_stocastico() {
  m_p            = 0;
  m_E            = 0;
  dt             = 0.5;   //valore a caso
  sigma          = 0.5;   //valore a caso
  risk_free_rate = 0.02;
  m_n_steps      = 0;
}



__device__ __host__ processo_stocastico::processo_stocastico(input_option_data option, input_market_data market, double* array_gauss) {
  m_p            = market.S_0;
  sigma          = market.sigma;
  risk_free_rate = market.risk_free_rate;

  m_E            = option.E;
  dt             = option.delta_t;
  m_n_steps      = option.num_intervals;

}
//destructor
__device__ __host__ processo_stocastico::~processo_stocastico() {
}

__device__ __host__ double processo_stocastico::eulero(double gauss) {
    double S;
    S = m_p;
    S = S*(1 + risk_free_rate*dt + sigma*sqrt(dt)*gauss);
  return S;  
}


/*__device__ __host__ double processo_stocastico::Get_new_price() {
  creazione_path();
  double dummy = m_p;
  return dummy;

}
  //payoff

__device__ __host__ double processo_stocastico::payoff() {

  return max((m_p - m_E), 0.);

}
*/
