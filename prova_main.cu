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

__device__ __host__ void pricer(double& media_prezzi, double& media_payoff, dati_anagrafici_opzione anagraf_data, input_option_data option, path thread_path, rng thread_rng, input_mc_data mc_data ) { //ipoteticamente posso passare il n_sim

  statistica stata(mc_data);
  payoff pay_off(anagraf_data, market_data, option_data);

  double * prezzi_finali = new double[mc_data.N_simulazioni];
  double * payoffs       = new double[mc_data.N_simulazioni];

    for (size_t i = 0; i < mc_data.N_simulazioni; i++) {

      double dummy = 0;

        for (size_t j = 0; j < option.num_intervals; j++) {

          dummy = thread_path.eulero(thread_rng.Get_gauss());

        }

      prezzi_finali[i] = dummy;
      payoffs[i] = pay_off.payoff_call(prezzi_finali[i]);

    }

  media_prezzi = stata.media(prezzi_finali);
  media_payoff = stata.media(payoffs);

// #### QUA IMPLEMENTO PAYOFF CORRIDOR ###


}


/*__global__ void simulator( input_mc_data mc_data, input_option_data option_data, input_market_data market_data) {
  int i = threadIdx.x + blockDim.x*blockIdx.x;

    rng thread_rng(1+i, 2345+i, 1234+i, 16545 +i);
  // dovrei passare tutte le classi e copiarle col copy constructor?
    path thread_path(option_data, market_data);



    // array_prova[i] = pricer(thread_path, thread_rng);
};
*/
int main() {

  // int N = 150;

  std::cout << "" << '\n';
  std::cout << "##########################################" << '\n';
  std::cout << "" << '\n';

  unsigned s1,s2,s3,s4;

  input_market_data market;
  input_option_data option;
  input_mc_data     data_montecarlo;

  set_struct_values(market, option, data_montecarlo);

  path path_creator(option, market);

  // cudaMalloc( (void **)&dev_array, 100*sizeof(double));

  // test_rng<<<2,20>>>(random_number_generator, path_creator, dev_array);

  // cudaMemcpy(array, dev_array, 100*sizeof(double), cudaMemcpyDeviceToHost);

  // cudaFree(dev_array);
