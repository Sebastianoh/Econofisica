#ifndef __processo_stocastico_h__
#define __processo_stocastico_h__
// #include "rng.h"

class processo_stocastico: public rng {

  public:
    processo_stocastico();
    processo_stocastico(double p, int n_steps, double E);
    ~processo_stocastico(); //destructor

    __device__ __host__ void eulero(double& S);
    __device__ __host__ void creazione_path();
    __device__ __host__ double payoff();
    __device__ __host__ double Get_new_price();
  // double black_and_scholes();
  private:

    double risk_free_rate;
    double m_p;
    double sigma;
    double dt;
    int m_n_steps;
    double m_E; //strike price, non so se considerarlo costante, o da passare al costruttore
};

#endif
