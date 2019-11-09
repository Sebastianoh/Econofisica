#ifndef __path_h__
#define __path_h__

#include "/home/sebastiano/Scrivania/airoldi/librerie/support_functions/struct.h"

class path {

  public:
    __device__ __host__ path();
    __device__ __host__ path(input_option_data o, input_market_data m);
    __device__ __host__ ~path(); //destructor

    // __device__ __host__ path(const path &path2);

    __device__ __host__ double GetPrice() ;
    __device__ __host__ void   eulero(double gauss);
    __device__ __host__ void   exact (double gauss);


    __device__ __host__ void   payoff_evaluator();
    __device__ __host__ double Get_payoff();
    __device__ __host__ double Get_controller();
    __device__ __host__ void corridor_controller(double, double);
    __device__ __host__ double Get_test() {return m_test_variable;}
    // double black_and_scholes();
  private:


    //dati mercato

    double m_payoff;

    double m_volatility;
    double m_risk_free_rate;
    double m_prezzo_iniziale;

    double m_price; //il prezzo dummy su cui fare eulero

    // dati opzione

    float  m_option_type;
    int    m_numero_steps;
    double m_delta_time;
    double m_time_to_maturity;
    double m_strike_price;

    //opzione corridor

    double m_B;
    double m_K;
    double m_N; //Nozionale
    int m_corridor; //sarebbe P_i della formula
    // int    m_date_fixing;

    int m_test_variable;
};

#endif
