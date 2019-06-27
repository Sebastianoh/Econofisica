#include <iostream>
#include <cmath>
#include <cstdlib>
#include "funzioni.h"
#include "rng.h"
#include "rng.cu"
#include "processo_stocastico.h"
#include "processo_stocastico.cu"

using namespace std;
//le global non posso definirle nelle classi

__global__ void pricer_montecarlo(processo_stocastico* pricer ,double * array_prezzi_finali) {

    int i = threadIdx.x + blockDim.x*blockIdx.x;
    // uso -> perché gli passo una classe by pointer
    array_prezzi_finali[i] = pricer->Get_new_price();

};

int main() {

  int N = 15000;

  unsigned s1 = 0;
  unsigned s2 = 0;
  unsigned s3 = 0;
  unsigned s4 = 0;

  random_seed_generator(s1,s2,s3,s4);

  rng random_number_generator(s1,s2,s3,s4);
  processo_stocastico host_pricer(10, 50, 12);

  double * prezzi     = new double [N];
  double * dev_prezzi = new double [N];

  //storage su cui copiare host pricer

  processo_stocastico *dev_pricer;

  cudaMalloc( (void **)&dev_pricer, N*sizeof(processo_stocastico) );
  cudaMalloc( (void **)&dev_prezzi, N*sizeof(double) );

  // copio:
  cudaMemcpy(&dev_pricer, &host_pricer, N*sizeof(processo_stocastico), cudaMemcpyHostToDevice);

  //prova senza troppe pretese,
  // still non funziona

  pricer_montecarlo<<<10,2>>>(dev_pricer, dev_prezzi);

  for (size_t i = 0; i < 15; i++) {
    std::cout << "prezzi : " << dev_prezzi[i] << '\n';
  };

  cudaMemcpy(prezzi, dev_prezzi, N*sizeof(double), cudaMemcpyDeviceToHost);

  cudaFree(dev_pricer);
  cudaFree(dev_prezzi);

    // prova
    // for (size_t i = 0; i < 15; i++) {
      // std::cout << "prezzi: " << prezzi[i] << '\n';
    // };

















return 0;
}
