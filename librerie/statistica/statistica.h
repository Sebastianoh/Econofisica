#ifndef __statistica_h__
#define __statistica_h__

#include "/home/sebastiano/Scrivania/airoldi/librerie/funzioni/struct.h"

class statistica {

  public:

    __device__ __host__ statistica();

    __device__ __host__ void   analisi(double payoff);

    __device__ __host__ double get_media();
    __device__ __host__ double get_somma_payoff();
    __device__ __host__ double get_somma_quadra_payoff();
    __device__ __host__ double get_deviazione_standard();


  private:

    int    m_step_simulazione;

    double m_media;
    double m_somma_payoff;
    double m_somma_quadra_payoff;
    double m_deviazione_standard;


};

#endif
