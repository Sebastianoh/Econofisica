#ifndef __processo_stocastico_h__
#define __processo_stocastico_h__

#include "struct.h"

// ########## ADESSO PROCESSO STOCASTICO NON EREDITA PIÙ DA RNG PERCHÉ NON MI ANDAVANO BENE I NUMERI GAUSS
// ######### HO DECISO DI PASSARLI AL COSTRUTTORE DEL PROCESSO. OVVIAMENTE PRIMA DEVO GENERARLI CON GET GAUSS
class processo_stocastico {

  public:
    __device__ __host__ processo_stocastico();
    __device__ __host__ processo_stocastico(input_option_data o, input_market_data m);
    __device__ __host__ ~processo_stocastico(); //destructor

    __device__ __host__ double eulero(double gauss);
    // __device__ __host__ double payoff();
    // __device__ __host__ double Get_new_price();
  // double black_and_scholes();
  private:

    double risk_free_rate;
    double m_p;
    double sigma;
    double dt;
    int    m_n_steps;
    double m_E; //strike price, non so se considerarlo costante, o da passare al costruttore

};

#endif
