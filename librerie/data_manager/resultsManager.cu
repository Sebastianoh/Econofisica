#include <string>
#include <fstream>
#include <iostream>
#include "resultsManager.h"
#include "/home/sebastiano/Scrivania/airoldi/librerie/funzioni/struct.h"

using namespace std;

void resultsManager::Set_Set_structs_value(&input_market_data, &input_option_data, &input_mc_data, string file) {

  ifstream myfile;
  myfile.open(file);

    if (myfile.is_open()) {
      std::cout << "file is open" << '\n';
    }

    while (!myfile.eof()) {

      char c;

        if (myfile.get() == c) {

          myfile.ignore(1000, '\n');

        }

      // market data
      myfile >> input_market_data.prezzo_iniziale; myfile >> input_market_data.risk_free_rate; myfile >> input_market_data.volatility;
      // option data
      myfile >> input_option_data.option_type; myfile >> input_option_data.numero_steps; myfile >> input_option_data.delta_time; myfile >> input_option_data.time_to_maturity; myfile >> input_option_data.strike_price; myfile >> input_option_data.B; myfile >> input_option_data.K; myfile >> input_option_data.N;
      // mc data
      myfile >> input_mc_data.N_simulazioni; myfile >> input_mc_data.N_tb; myfile >> input_mc_data.N_b;

    }

}

void resultsManager::Set_output_file(string file) {

  ofstream myfile;
  myfile.open(file);

  if (myfile.is_open()) {
    std::cout << "file is open " << '\n';
  }

}
