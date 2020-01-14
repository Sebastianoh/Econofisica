#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/path/path.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/statistica/statistica.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/random_generator/rng.cuh"

/*__device__*/ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, int thread_number) {

  //ovviamente così non è bello, bisogna generarne uno per ogni simulazione che voglio
  path path_simulator(option_data, market_data);

  // std::cout << "rand numbers:  " << s1 << ", " << s2 << ", " << s3 << ", "  << s4 << '\n';
  // statistica *stat1 = new statistica[mc_data.N_simulazioni];
  statistica stat;

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      int s1,s2,s3,s4;
      s1 = rand() % 100000;
      s2 = rand() % 128 +100000;
      s3 = rand() % 128 +100000;
      s4 = rand() % 128 +100000;

      rng  test_generator(s1,s2,s3,s4);
      // stat1[i].set_state(stat2);

        for (size_t j = 0; j < option_data.numero_steps; j++) {

          path_simulator.eulero(test_generator.Get_gauss());

        }

      path_simulator.payoff_evaluator();
      stat.analisi(path_simulator.Get_payoff() );

      output[thread_number].media_payoff = stat.get_media();
      output[thread_number].dev_standard = stat.get_deviazione_standard();

      path_simulator.reset_price(market_data);

    }

}

 // GLOBAL
/*
__global__ void GPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output ) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  montecarlo_simulator(market_data, option_data, mc_data, output, i);
}
//

__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data) {

/*
  cudaEvent_t gpuEventStart, gpuEventStop;
	double gpuElapsedTime;
	cudaEventCreate(&gpuEventStart);
	cudaEventCreate(&gpuEventStop);


  int dummy_thread_number = 1000;

//CPU OUTPUT VECTOR
  output_statistica * output = new output_statistica[dummy_thread_number];
//DEV OUTPUT VECTOR
  output_statistica * dev_output;

// SOME CUDA SHIT
  cudaMalloc((void **)&dev_output, dummy_thread_number*sizeof(output_statistica));
  cudaMemcpy(dev_output, output, dummy_thread_number*sizeof(output_statistica), cudaMemcpyHostToDevice);

// INVOCO LA GLOBAL
  GPU_montecarlo_simulator<<<1,1>>>(market_data, option_data, mc_data, dev_output);

// SOME CUDA SHIT
  cudaMemcpy(output, dev_output, dummy_thread_number*sizeof(output_statistica), cudaMemcpyDeviceToHost);
  cudaFree(dev_output);

}
*/

// DEVO FARE LA CPU-GPU SIMULATOR
__host__ void CPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output ) {

  int dummy_thread_number = 1000;

    for (size_t i = 0; i < dummy_thread_number ; i++) {

      montecarlo_simulator(market_data, option_data, mc_data, output, i);
    }

}
