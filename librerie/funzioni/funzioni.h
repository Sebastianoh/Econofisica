#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "../path/path.h"
#include "../statistica/statistica.h"
#include "../random_generator/rng.cuh"
#include "../random_generator/auxiliary.h"

__device__ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, int thread_number, unsigned int seed) {

  statistica stat;
  path path_simulator(option_data, market_data);

  auxiliary* auxiliar_generator = new auxiliary(seed + thread_number);
  rng* thread_generator = new rng;
  thread_generator->set_initial_state(auxiliar_generator);

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      path_simulator.reset_price(market_data);

        for (size_t j = 0; j < option_data.numero_steps; j++) {

          path_simulator.eulero(thread_generator->Get_gauss());

        }

      path_simulator.payoff_evaluator();
      stat.analisi(path_simulator.Get_payoff() );

      output[thread_number].media_payoff = stat.get_media();
      output[thread_number].dev_standard = stat.get_deviazione_standard();

      // std::cout << "test:  " << output[thread_number].media_payoff <<'\n';

    }

}

 // GLOBAL
/*
__global__ void GPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned * array1, unsigned * array2, unsigned * array3, unsigned * array4 ) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  montecarlo_simulator(market_data, option_data, mc_data, output, i, array1, array2, array3, array4);

}

__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output) {

  unsigned *array1 = new unsigned[mc_data.N_simulazioni];
  unsigned *array2 = new unsigned[mc_data.N_simulazioni];
  unsigned *array3 = new unsigned[mc_data.N_simulazioni];
  unsigned *array4 = new unsigned[mc_data.N_simulazioni];

  unsigned *dev_array1;
  unsigned *dev_array2;
  unsigned *dev_array3;
  unsigned *dev_array4;

  set_random_vector(array1, array2, array3, array4, mc_data);

  cudaMalloc((void **)&dev_array1, mc_data.N_simulazioni*sizeof(unsigned));
  cudaMalloc((void **)&dev_array2, mc_data.N_simulazioni*sizeof(unsigned));
  cudaMalloc((void **)&dev_array3, mc_data.N_simulazioni*sizeof(unsigned));
  cudaMalloc((void **)&dev_array4, mc_data.N_simulazioni*sizeof(unsigned));

  cudaMemcpy(dev_array1, array1, mc_data.N_simulazioni*sizeof(unsigned), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_array2, array2, mc_data.N_simulazioni*sizeof(unsigned), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_array3, array3, mc_data.N_simulazioni*sizeof(unsigned), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_array4, array4, mc_data.N_simulazioni*sizeof(unsigned), cudaMemcpyHostToDevice);

  // std::cout << "test 0" << '\n';

  output_statistica * dev_output;

  // std::cout << "test 1" << '\n';

  cudaMalloc((void **)&dev_output, gpu_data.numero_thread_totali*sizeof(output_statistica));
  cudaMemcpy(dev_output, output,   gpu_data.numero_thread_totali*sizeof(output_statistica), cudaMemcpyHostToDevice);

  GPU_montecarlo_simulator<<<gpu_data.numero_thread_per_blocco,gpu_data.numero_blocchi>>>(market_data, option_data, mc_data, dev_output, dev_array1, dev_array2, dev_array3, dev_array4);

  cudaMemcpy(output, dev_output, gpu_data.numero_thread_totali*sizeof(output_statistica), cudaMemcpyDeviceToHost);

  // std::cout << "test 2" << '\n';

  cudaFree(dev_output);
  cudaFree(dev_array1);
  cudaFree(dev_array2);
  cudaFree(dev_array3);
  cudaFree(dev_array4);

  delete[] array1, array2, array3, array4;
  // delete[] dev_array1, dev_array2, dev_array3, dev_array4;

}
*/
// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output, unsigned int seed) {
  //
  // unsigned * rand_vec1 = new unsigned[mc_data.N_simulazioni];
  // unsigned * rand_vec2 = new unsigned[mc_data.N_simulazioni];
  // unsigned * rand_vec3 = new unsigned[mc_data.N_simulazioni];
  // unsigned * rand_vec4 = new unsigned[mc_data.N_simulazioni];


    for (int i = 0; i < gpu_data.numero_thread_totali; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i, seed);

    }
  // //
  // delete[] rand_vec1;
  // delete[] rand_vec2;
  // delete[] rand_vec3;
  // delete[] rand_vec4;
  // //

}


__host__ void CPU_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output) {

  unsigned int seed = 7;

  CPU_montecarlo_simulator(market_data, option_data, mc_data, gpu_data, output, seed);

}
