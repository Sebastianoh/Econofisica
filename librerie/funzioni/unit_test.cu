#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "struct.h"
#include "funzioni.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/path/path.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/statistica/statistica.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/random_generator/rng.cuh"

//14-11 PROBLEMA! Devo resettare il prezzo iniziale o si incrementa sempre e non è buono

int main() {

  input_mc_data mc_data         = {100,1,1};
  input_market_data market_data = {100, 0.01, 0.2};
  input_option_data option_data = {1, 10, 1, 1, 100, 0.25, 0, 1};

  output_statistica *output = new output_statistica[mc_data.N_simulazioni];

    for (int i = 0; i < 10; i++) {
      /* code */
      montecarlo_simulator(market_data, option_data, mc_data, output, i);

    }

  for (size_t j = 0; j < 10; j++) {

    std::cout << "test 1:     " << output[j].media_payoff << '\n';
    std::cout << "test dev:   " << output[j].dev_standard << '\n';

  }

return 0;

}
