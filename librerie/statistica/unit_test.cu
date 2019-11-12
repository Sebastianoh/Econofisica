#include <iostream>
#include <cmath>
#include "/home/sebastiano/Scrivania/airoldi/librerie/support_functions/struct.h"
#include "statistica.h"

using namespace std;

int main() {

  input_mc_data data_montecarlo = {10,1,1};
  statistica test_stata(data_montecarlo);

    for (size_t i = 0; i < data_montecarlo.N_simulazioni; i++) {

      double dummy = 10/(1+i);
      test_stata.analisi(dummy);

    }


  std::cout << "################################" << '\n';
  std::cout << "test 1, somma:           " << test_stata.get_somma_payoff() << '\n';
  std::cout << "################################" << '\n';
  std::cout << " " << '\n';
  std::cout << "################################" << '\n';
  std::cout << "test 2, somma quadra:    " << test_stata.get_somma_quadra_payoff() << '\n';
  std::cout << "################################" << '\n';
  std::cout << " " << '\n';
  std::cout << "################################" << '\n';
  std::cout << "test 3, media:           " << test_stata.get_media() << '\n';
  std::cout << "################################" << '\n';
  std::cout << " " << '\n';
  std::cout << "################################" << '\n';
  std::cout << "test 4, dev_std:         " << test_stata.get_deviazione_standard() << '\n';
  std::cout << "################################" << '\n';

return 0;
}
