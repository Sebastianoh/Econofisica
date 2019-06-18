#ifndef __processo_stocastico_h__
#define __processo_stocastico_h__
// #include "rng.h"

class processo_stocastico: public rng {

  public:

    //a processo stocastico passo un prezzo iniziale p e il numero di intervalli per fare i path

    processo_stocastico(double p, int n_steps, double E);
    ~processo_stocastico(); //destructor

    void eulero(double& S);
    void creazione_path();
    double payoff();
    double Get_new_price();
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
