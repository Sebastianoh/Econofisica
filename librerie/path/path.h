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
    // __device__ __host__ path(const path &path2);


    __device__ __host__ double eulero(double gauss);
    __device__ __host__ double payoff();
    // __device__ __host__ double Get_new_price();
    // double black_and_scholes();
  private:

    //dati mercato

    double m_risk_free_rate;
    double m_prezzo_iniziale;
    double m_volatility;

    double step_price //il prezzo dummy su cui fare eulero

    // dati opzione

    char   m_option_type;
    int    m_numero_steps;
    double delta_time;
    double m_time_to_maturity;
    double m_strike_price;

    //opzione corridor

    double m_B;
    double m_K;
    double m_N; //Nozionale


};

#endif
