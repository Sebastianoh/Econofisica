#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/path/path.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/statistica/statistica.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/random_generator/rng.cuh"

//funzioni di supporto?
  // 1- mi serve una funzione da chiamare che carica le strutture ma non iostream
  // 2- voglio una funzione che simuli un MC -> adesso la creo:
  // 3- per ora facciamo test semplici poi lo rendiamo complicato come ci pare

__device__ __host__ void montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output, int thread_number) {

  //ovviamente così non è bello, bisogna generarne uno per ogni simulazione che voglio
  path path_simulator(option_data, market_data);

  // statistica *stat1 = new statistica[mc_data.N_simulazioni];
  statistica stat;

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      rng  test_generator(1+i, 23456+i - 2*i, 1529+i, 2340567+i);
      // stat1[i].set_state(stat2);

        for (size_t j = 0; j < option_data.numero_steps; j++) {

          path_simulator.eulero(test_generator.Get_gauss());

        }

      path_simulator.payoff_evaluator();
      stat.analisi(path_simulator.Get_payoff() );

      // std::cout << "price     " << path_simulator.GetPrice() <<'\n';

      output[thread_number].media_payoff = stat.get_media();
      output[thread_number].dev_standard = stat.get_deviazione_standard();

      path_simulator.reset_price(market_data);
    }

}

 // GLOBAL
//
__global__ void GPU_montecarlo_simulator(input_market_data market_data, input_option_data option_data, input_mc_data mc_data, output_statistica* output ) {

  int i = threadIdx.x + blockDim.x * blockIdx.x;

  montecarlo_simulator(market_data, option_data, mc_data, output, i);
}
//

__host__ void global_caller(input_market_data market_data, input_option_data option_data, input_mc_data mc_data) {

// è arrivato dicembre e siamo ancora qua...
// devo creare una classe per leggere da file e scrivere su un file

/*
  cudaEvent_t gpuEventStart, gpuEventStop;
	double gpuElapsedTime;
	cudaEventCreate(&gpuEventStart);
	cudaEventCreate(&gpuEventStop);
*/

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
