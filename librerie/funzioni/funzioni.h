#include <cmath>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <iostream>

#include "struct.h"
#include "../path/path.h"
#include "../statistica/statistica.h"
#include "../random_generator/rng.cuh"
#include "../random_generator/auxiliary.h"
#include "../data_manager/resultsManager.h"

__device__ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned int thread_number, unsigned int seed) {

  statistica stat;
  path path_simulator(option_data, market_data);

  auxiliary* auxiliar_generator = new auxiliary(seed + thread_number);
  rng* thread_generator = new rng;
  thread_generator->set_initial_state(auxiliar_generator);

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      path_simulator.reset_price(market_data);

        for (size_t j = 0; j < option_data.numero_steps; j++) {

//          path_simulator.eulero(thread_generator->Get_gauss());
            path_simulator.exact(thread_generator->Get_gauss());

        }

      path_simulator.payoff_evaluator();
      stat.analisi(path_simulator.Get_payoff());

      output[thread_number].media_payoff = stat.get_media();
      output[thread_number].dev_standard = stat.get_deviazione_standard();

    }

}

 // GLOBAL

__global__ void GPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, unsigned int seed) {

  unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;

  montecarlo_simulator(market_data, option_data, mc_data, output, i, seed);

}

__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data /*, output_statistica* output*/) {

  std::string output_file_gpu("./data_manager/output_file_gpu.dat");

  unsigned int seed = 7;
  resultsManager printer;

 
  output_statistica *output_gpu = new output_statistica[gpu_data.numero_thread_totali];	
  output_statistica * dev_output;

  
  cudaMalloc((void **)&dev_output, gpu_data.numero_thread_totali*sizeof(output_statistica));
  cudaMemcpy(dev_output, output_gpu,   gpu_data.numero_thread_totali*sizeof(output_statistica), cudaMemcpyHostToDevice);
  
  std::cout << "test 1" << '\n';
  
  GPU_montecarlo_simulator<<<gpu_data.numero_blocchi,gpu_data.numero_thread_per_blocco>>>(market_data, option_data, mc_data, dev_output, seed);
  
  std::cout << "test 2" << '\n';
  
  cudaMemcpy(output_gpu, dev_output, gpu_data.numero_thread_totali*sizeof(output_statistica), cudaMemcpyDeviceToHost);
 
  std::cout << "test 3" << '\n';

  
  cudaFree(dev_output);

  printer.Print(output_file_gpu, output_gpu, gpu_data);

  delete[] output_gpu;
}
// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output, unsigned int seed) {
    for (int i = 0; i < gpu_data.numero_thread_totali; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i, seed);

    }
}


__host__ void CPU_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, input_gpu_data gpu_data, output_statistica* output) {

  unsigned int seed = 7;

  CPU_montecarlo_simulator(market_data, option_data, mc_data, gpu_data, output, seed);

}

//ciao
