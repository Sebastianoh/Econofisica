// ############## MAIN PER FARE I TEST ############

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "rng.h"
#include "rng.cu"
#include "struct.h"
#include "funzioni.h"
#include "path.h"

using namespace std;
//le global non posso definirle nelle classi

__device__ __host__ double pricer(path thread_path, rng thread_rng ) {
  double dummy = 0;
      for (size_t j = 0; j < 10; j++) {
        dummy = thread_path.eulero(thread_rng.Get_gauss());
      }
  return dummy;
}

__global__ void test_rng(path P, double * array_prova) {
  int i = threadIdx.x + blockDim.x*blockIdx.x;

    rng thread_rng(1+i, 2345+i, 1234+i, 16545 +i);
    path thread_path = P;

    array_prova[i] = pricer(thread_path, thread_rng);
};

int main() {

  // int N = 150;

  std::cout << "" << '\n';
  std::cout << "##########################################" << '\n';
  std::cout << "" << '\n';

  unsigned s1,s2,s3,s4;
  double * array = new double [100];
  double * dev_array = new double [100];

  input_market_data market;
  input_option_data option;
  input_mc_data     data_montecarlo;

  set_struct_values(market, option, data_montecarlo);

  path path_creator(option, market);

  cudaMalloc( (void **)&dev_array, 100*sizeof(double));

  test_rng<<<2,20>>>(random_number_generator, path_creator, dev_array);

  cudaMemcpy(array, dev_array, 100*sizeof(double), cudaMemcpyDeviceToHost);

  cudaFree(dev_array);

    for (size_t i = 0; i < 10; i++) {
      std::cout << "array:" << array[i] << '\n';
    }

return 0;
}
