#include "processo_stocastico.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

processo_stocastico::processo_stocastico(double p) {

  m_p            = p;
  dt             = 0.5;   //valore a caso
  sigma          = 0.5;   //valore a caso
  risk_free_rate = 0.02;

}
//destructor
processo_stocastico::~processo_stocastico() {
}

void processo_stocastico::eulero(double& S) {

  S = S*(1 + risk_free_rate*dt + sigma*sqrt(dt)*rng::Get_gauss());

}

double processo_stocastico::Get_new_price() {
  eulero(m_p);
  return m_p;
}
