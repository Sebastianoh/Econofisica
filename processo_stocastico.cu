#include "processo_stocastico.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

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

void processo_stocastico::eulero(double& S) {

  S = S*(1 + risk_free_rate*dt + sigma*sqrt(dt)*rng::Get_gauss());
}

void processo_stocastico::creazione_path(){

  for (size_t i = 0; i < m_n_steps; i++) {
    eulero(m_p);
  };
}

double processo_stocastico::Get_new_price() {
  creazione_path();
  return m_p;
}

double processo_stocastico::payoff() {

  return max((m_p - m_E), 0);

}
