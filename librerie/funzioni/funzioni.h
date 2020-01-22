#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "../path/path.h"
#include "../statistica/statistica.h"
#include "../random_generator/rng.cuh"


__host__ void set_random_vector (unsigned  * &(array)) {

  for (size_t i = 0; i < 10000; i++) {
    array[i] = rand() % 128 + 100000;

  }
}

__device__ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, int thread_number, unsigned * rand_vec) {

  statistica stat;
  path path_simulator(option_data, market_data);

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      rng  thread_generator(rand_vec[i+thread_number],rand_vec[i+thread_number+1],rand_vec[i+thread_number+2],rand_vec[i+thread_number+3]);

        for (size_t j = 0; j < option_data.numero_steps; j++) {

          path_simulator.eulero(thread_generator.Get_gauss());

        }

      path_simulator.payoff_evaluator();
      stat.analisi(path_simulator.Get_payoff() );

      output[thread_number].media_payoff = stat.get_media();
      output[thread_number].dev_standard = stat.get_deviazione_standard();

      path_simulator.reset_price(market_data);

    }

}

 // GLOBAL

__global__ void GPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned * rand_vec) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  montecarlo_simulator(market_data, option_data, mc_data, output, i, rand_vec);

}

__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output) {

  std::cout << " test -2 " << '\n';
	
	int *dev_a;
	cudaMalloc((void**)&dev_a, 2*sizeof(int));

  unsigned *array = new unsigned[mc_data.N_simulazioni];
  unsigned *dev_array;
  set_random_vector(array);



// il vettore di output glielo passo dalla funzia
  output_statistica * dev_output;

// rand vec
	std::cout <<" ho il diocane " << '\n';
  cudaMalloc((void **)&dev_array, sizeof(unsigned));
  std::cout << " test -1 " << '\n';
  cudaMemcpy(dev_array, array, sizeof(double), cudaMemcpyHostToDevice);

	  std::cout << "test 0" << '\n';

// output vec
  cudaMalloc((void **)&dev_output, mc_data.N_simulazioni*sizeof(output_statistica));
  cudaMemcpy(dev_output, output, mc_data.N_simulazioni*sizeof(output_statistica), cudaMemcpyHostToDevice);

// INVOCO LA GLOBAL
// dovrei passare la struct dati gpu

  std::cout << "test 1" << '\n';


  GPU_montecarlo_simulator<<<1,1>>>(market_data, option_data, mc_data, dev_output, dev_array);

  std::cout << "test 2" << '\n';


  cudaMemcpy(output, dev_output, mc_data.N_simulazioni*sizeof(output_statistica), cudaMemcpyDeviceToHost);
  cudaFree(dev_output);
  cudaFree(dev_array);

  delete[] array, dev_array;
}


// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned * rand_vec) {

  int dummy_thread_number = 1000;

    for (size_t i = 0; i < dummy_thread_number ; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i, rand_vec);

    }


}


__host__ void CPU_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output) {

  unsigned * array = new unsigned[mc_data.N_simulazioni];
  set_random_vector(array);

  CPU_montecarlo_simulator(market_data, option_data, mc_data, output, array);
 
  delete[] array;

}
