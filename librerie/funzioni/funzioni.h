#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/path/path.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/statistica/statistica.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/random_generator/rng.cuh"

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
//


__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data) {

/*
  cudaEvent_t gpuEventStart, gpuEventStop;
	double gpuElapsedTime;
	cudaEventCreate(&gpuEventStart);
	cudaEventCreate(&gpuEventStop);
*/
// SET RANDOM SEED VECTOR

  unsigned * array = new unsigned[mc_data.N_simulazioni];
  unsigned * dev_array;
  set_random_vector(array);


  int dummy_thread_number = 1000;

//CPU OUTPUT VECTOR
  output_statistica * output = new output_statistica[dummy_thread_number];
//DEV OUTPUT VECTOR
  output_statistica * dev_output;

// SOME CUDA SHIT
  cudaMalloc((void **)&dev_array, dummy_thread_number*sizeof(array));
  cudaMemcpy(dev_array, array, dummy_thread_number*sizeof(array), cudaMemcpyHostToDevice);

  cudaMalloc((void **)&dev_output, dummy_thread_number*sizeof(output_statistica));
  cudaMemcpy(dev_output, output, dummy_thread_number*sizeof(output_statistica), cudaMemcpyHostToDevice);

// INVOCO LA GLOBAL
  GPU_montecarlo_simulator<<<1,1>>>(market_data, option_data, mc_data, dev_output, dev_array);

// SOME CUDA SHIT
  cudaMemcpy(output, dev_output, dummy_thread_number*sizeof(output_statistica), cudaMemcpyDeviceToHost);
  cudaFree(dev_output);

}


// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned * rand_vec) {

  int dummy_thread_number = 1000;

    for (size_t i = 0; i < dummy_thread_number ; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i, rand_vec);

    }


}


__host__ void CPU_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output) {

  // devo creare qua il vettore rand

  // output_statistica *output = new output_statistica[mc_data.N_simulazioni];
  // vettore di output glielo debbo passare by reference per farglielo modificare? I guess

  unsigned * array = new unsigned[mc_data.N_simulazioni];
  set_random_vector(array);

  CPU_montecarlo_simulator(market_data, option_data, mc_data, output, array);

}
