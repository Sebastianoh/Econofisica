#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "../path/path.h"
#include "../statistica/statistica.h"
#include "../random_generator/rng.cuh"


__host__ void set_random_vector (unsigned * array1, unsigned * array2, unsigned * array3, unsigned * array4, input_mc_data mc_data) {

  for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

    array1[i] = rand() % 128 + 100000;
    array2[i] = rand() % 128 + 100000;
    array3[i] = rand() % 128 + 100000;
    array4[i] = rand() % 128 + 100000;

  }
}

__device__ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, int thread_number, unsigned * array1, unsigned * array2, unsigned * array3, unsigned * array4) {

  statistica stat;
  path path_simulator(option_data, market_data);

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      rng  thread_generator(array1[i], array2[i], array3[i], array4[i]);

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

  std::cout << "test 0" << '\n';

  output_statistica * dev_output;

  std::cout << "test 1" << '\n';

  cudaMalloc((void **)&dev_output, mc_data.N_simulazioni*sizeof(output_statistica));
  cudaMemcpy(dev_output, output,   mc_data.N_simulazioni*sizeof(output_statistica), cudaMemcpyHostToDevice);

  GPU_montecarlo_simulator<<<gpu_data.numero_thread_per_blocco,gpu_data.numero_blocchi>>>(market_data, option_data, mc_data, dev_output, dev_array1, dev_array2, dev_array3, dev_array4);

  cudaMemcpy(output, dev_output, mc_data.N_simulazioni*sizeof(output_statistica), cudaMemcpyDeviceToHost);

  std::cout << "test 2" << '\n';

  cudaFree(dev_output);
  cudaFree(dev_array1);
  cudaFree(dev_array2);
  cudaFree(dev_array3);
  cudaFree(dev_array4);

  delete[] array1, array2, array3, array4;
  // delete[] dev_array1, dev_array2, dev_array3, dev_array4;

}

// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output) {

  unsigned * rand_vec1 = new unsigned[mc_data.N_simulazioni];
  unsigned * rand_vec2 = new unsigned[mc_data.N_simulazioni];
  unsigned * rand_vec3 = new unsigned[mc_data.N_simulazioni];
  unsigned * rand_vec4 = new unsigned[mc_data.N_simulazioni];

  set_random_vector(rand_vec1, rand_vec2, rand_vec3, rand_vec4, mc_data);

    for (int i = 0; i < gpu_data.numero_thread_totali; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i, rand_vec1, rand_vec2, rand_vec3, rand_vec4);

    }

  delete[] rand_vec1;
  delete[] rand_vec2;
  delete[] rand_vec3;
  delete[] rand_vec4;


}


__host__ void CPU_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output) {

  std::cout << "test 1" << '\n';

  CPU_montecarlo_simulator(market_data, option_data, mc_data, gpu_data, output);

  std::cout << "test 2" << '\n';


}
