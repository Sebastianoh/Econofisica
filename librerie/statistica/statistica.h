#ifndef __statistica_h__
#define __statistica_h__

#include "/home/sebastiano/Scrivania/airoldi/librerie/support_functions/struct.h"

class statistica {

  public:
    __device__ __host__ statistica(input_mc_data M);

    __device__ __host__ void analisi(double payoff);

    __device__ __host__ double get_media();
    __device__ __host__ double get_somma_payoff();
    __device__ __host__ double get_somma_quadra_payoff();
    __device__ __host__ double get_deviazione_standard();


  private:

    int    m_num_simulazioni;

    double m_media;
    double m_somma_payoff;
    double m_somma_quadra_payoff;
    double m_deviazione_standard;


};

#endif
