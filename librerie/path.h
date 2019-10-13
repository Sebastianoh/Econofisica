#ifndef __path_h__
#define __path_h__

#include "struct.h"

// ########## ADESSO PROCESSO STOCASTICO NON EREDITA PIÙ DA RNG PERCHÉ NON MI ANDAVANO BENE I NUMERI GAUSS
// ######### HO DECISO DI PASSARLI AL COSTRUTTORE DEL PROCESSO. OVVIAMENTE PRIMA DEVO GENERARLI CON GET GAUSS
class path {

  public:
    __device__ __host__ path();
    __device__ __host__ path(input_option_data o, input_market_data m);
    __device__ __host__ ~path(); //destructor
    __device__ __host__ path(const path &path2);


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
