// ############## MAIN PER FARE I TEST ############

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "rng.h"
#include "rng.cu"
#include "struct.h"
#include "funzioni.h"
#include "processo_stocastico.h"
#include "processo_stocastico.cu"


using namespace std;
//le global non posso definirle nelle classi

__global__ void test_rng( double * array_prova) {

    // processo_stocastico host_pricer(10, 50, 12);

    // int i = threadIdx.x + blockDim.x*blockIdx.x;

    // processo_stocastico gpu_pricer(100, 1, 100);
    // uso -> perché gli passo una classe by pointer
    // array_prova[i] = host_pricer.Get_new_price();

};

int main() {

  // int N = 150;

  unsigned s1 = 0;
  unsigned s2 = 0;
  unsigned s3 = 0;
  unsigned s4 = 0;

  input_market_data market;
  input_option_data option;

  random_seed_generator(s1,s2,s3,s4);
  set_struct_values(market, option);

  rng random_number_generator(s1,s2,s3,s4);
  //struct option, struct data
  processo_stocastico host_pricer(option, market);

  for (size_t i = 0; i < 10; i++) {
    std::cout << "prova: " << host_pricer.Get_gauss() << '\n';
  }


return 0;
}
