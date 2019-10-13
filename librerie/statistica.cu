#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "statistica.h"

__device__ __host__ statistica::statistica(input_mc_data M) {

   m_size = M.N_simulazioni;  //la size del vettore è il numero di simulazioni montecarlo
    //passo la struttura con dentro anche il numero di simulazioni monte a questa classe così lo conosco
    // for (size_t i = 0; i < m_size; i++) {
      // m_array[i] = array [i];
    // }

};

__device__ __host__ double media(double * array) {
  double somma = 0;
  double media = 0;
    for (size_t i = 0; i < m_size; i++) {
      double somma_dummy = array[i];
      somma += somma_dummy;
    }
  media = somma/m_size;
  return media;
}
