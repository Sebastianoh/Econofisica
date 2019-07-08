#include <iostream>
#include <cmath>
#include <cstdlib>
#include "path.h"
#include "rng.h"

__device__ __host__ path::path() {
  m_p            = 0;
  m_E            = 0;
  dt             = 0.5;   //valore a caso
  sigma          = 0.5;   //valore a caso
  risk_free_rate = 0.02;
  m_n_steps      = 0;
}



__device__ __host__ path::path(input_option_data option, input_market_data market) {
  m_p            = market.S_0;
  sigma          = market.sigma;
  risk_free_rate = market.risk_free_rate;

  m_E            = option.E;
  dt             = option.delta_t;
  m_n_steps      = option.num_intervals;

}

__device__ __host__ path::path(const path &path2) {
  m_p            = path2.m_p;
  sigma          = path2.sigma;
  risk_free_rate = path2.risk_free_rate;

  m_E            = path2.m_E;
  dt             = path2.dt;
  m_n_steps      = path2.m_n_steps;

}



//destructor
__device__ __host__ path::~path() {
}

__device__ __host__ double path::eulero(double gauss) {
    double S;
    S = m_p;
    S = S*(1 + risk_free_rate*dt + sigma*sqrt(dt)*gauss);
  return S;
}


/*__device__ __host__ double path::Get_new_price() {
  creazione_path();
  double dummy = m_p;
  return dummy;

}
  //payoff

__device__ __host__ double path::payoff() {

  return max((m_p - m_E), 0.);

}
*/
