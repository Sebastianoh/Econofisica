#ifndef __processo_stocastico_h__
#define __processo_stocastico_h__
// #include "rng.h"

class processo_stocastico: public rng {

  public:

    processo_stocastico(double p);
    ~processo_stocastico(); //destructor

    void eulero(double& S);
    double Get_new_price (); 
  // double black_and_scholes();
  private:

    double risk_free_rate;
    double m_p;
    double sigma;
    double dt;

};

#endif
