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

__global__ void test_rng( double * array_prova) {

    processo_stocastico host_pricer(10, 50, 12); 
    
    int i = threadIdx.x + blockDim.x*blockIdx.x;

    // processo_stocastico gpu_pricer(100, 1, 100);
    // uso -> perché gli passo una classe by pointer
    array_prova[i] = host_pricer.Get_new_price();

};

int main() {

  int N = 150;

  unsigned s1 = 0;
  unsigned s2 = 0;
  unsigned s3 = 0;
  unsigned s4 = 0;

  random_seed_generator(s1,s2,s3,s4);

  // rng random_number_generator(s1,s2,s3,s4);
  processo_stocastico host_pricer(10, 50, 12);



// std::cout << "1:  " << host_pricer.Get_gauss()     << '\n';
// std::cout << "2:  " << host_pricer.Get_uniform()   << '\n';
// std::cout << "3:  " << host_pricer.Get_new_price() << '\n';


  double * prezzi     = new double [N];
  double * dev_prezzi = new double [N];

  //storage su cui copiare host pricer

  // processo_stocastico *dev_pricer;

  // cudaMalloc( (void **)&dev_pricer, sizeof(processo_stocastico) );
  cudaMalloc( (void **)&dev_prezzi, N*sizeof(double) );

  // copio:
  // cudaMemcpy(&dev_pricer, &host_pricer, sizeof(processo_stocastico), cudaMemcpyHostToDevice);

  //prova senza troppe pretese,
  // still non funziona
  test_rng<<<2,2>>>(dev_prezzi);

  cudaMemcpy(prezzi, dev_prezzi, N*sizeof(double), cudaMemcpyDeviceToHost);
  // cudaFree(dev_pricer);

for (size_t i = 0; i < 10; i++) {
  std::cout << "prezzi:  " << prezzi[i] <<'\n';
  /* code */
}



  cudaFree(dev_prezzi);

return 0;
}
