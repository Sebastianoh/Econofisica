// ############## MAIN PER FARE I TEST ############

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "rng.h"
#include "rng.cu"
#include "struct.h"
#include "funzioni.h"
#include "montecarlo.h"
#include "montecarlo.cu"
#include "path.h"
#include "path.cu"

using namespace std;
//le global non posso definirle nelle classi


// __global__ void test_rng( double * array_prova) {

    // path host_pricer(10, 50, 12);

    // int i = threadIdx.x + blockDim.x*blockIdx.x;

    // path gpu_pricer(100, 1, 100);
    // uso -> perché gli passo una classe by pointer
    // array_prova[i] = host_pricer.Get_new_price();

// };

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
  random_seed_generator(s1,s2,s3,s4);

  rng random_number_generator(s1,s2,s3,s4);

  path path_creator(option, market);

  // ################ CREO UN PATH

  double final_price_test[data_montecarlo.N_tb][option.num_intervals];

    for (size_t j = 0; j < data_montecarlo.N_tb; j++) {


      for (size_t i = 0; i < option.num_intervals; i++) {

        final_price_test[j][i] = path_creator.eulero(random_number_generator.Get_gauss());
        std::cout << "final_price_test:   " << final_price_test[j][i] << '\n';

      }
    }
  std::cout << "" << '\n';
  std::cout << "##########################################" << '\n';
  std::cout << "" << '\n';

  // montecarlo          pricer_mc(data_montecarlo);

  //struct option, struct data



return 0;
}
