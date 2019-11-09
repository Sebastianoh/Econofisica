#include "path.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/support_functions/struct.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/random_generator/rng.cuh"

#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

  int main() {

    rng test_generator(1, 762, 129, 234567);

    input_market_data market_data          = {100, 0.01, 0.01};
    input_option_data option_data          = {0, 100, 1, 1, 100, 0, 0, 1};
    input_option_data option_data_plain    = {1, 100, 1, 1, 100, 0, 0, 1};
    input_option_data option_data_corridor = {2, 100, 1, 1, 100, 0.5, 0, 1};

    //farò una funzione che le carica... in realtà ce l'ho, però per ora bona
    // poi dovrei farla da file...

    //  PRIMA OPTION POI MARKET

    path simulator(option_data, market_data);

    std::cout << "valutando il payoff... :  " << '\n';
    std::cout << "#######################" << '\n';

    simulator.payoff_evaluator();

    std::cout << "test payoff :  " << simulator.Get_payoff() << '\n';
    std::cout << "#######################" << '\n';

    path simulator_plain(option_data_plain, market_data);
    path simulator_corridor(option_data_corridor, market_data);

      for (size_t i = 0; i < option_data.numero_steps ; i++) {

        simulator_plain.eulero(test_generator.Get_gauss());
        simulator_corridor.eulero(test_generator.Get_gauss());

      }

    std::cout << "test 2:  "          << simulator_plain.GetPrice() << '\n';
    std::cout << "###################" << '\n';
    std::cout << "valutando il payoff  2 ... :  " << '\n';

    simulator_plain.payoff_evaluator();

    std::cout << "###################" << '\n';
    std::cout << "test payoff 2:  " << simulator_plain.Get_payoff() << '\n';
    std::cout << "###################" << '\n';

    std::cout << " "          << '\n';
    std::cout << "test 3:  "  << simulator_corridor.GetPrice() << '\n';
    std::cout << "###################" << '\n';
    std::cout << "valutando il payoff  3 ... :  " << '\n';

    simulator_corridor.payoff_evaluator();

    std::cout << "###################" << '\n';
    std::cout << "test controller 3:  " << simulator_corridor.Get_controller() << '\n';
    std::cout << "test dummy variable :  " << simulator_corridor.Get_test() << '\n';


    std::cout << "test payoff 3:  " << simulator_corridor.Get_payoff() << '\n';
    std::cout << "###################" << '\n';

  return 0;

  }
