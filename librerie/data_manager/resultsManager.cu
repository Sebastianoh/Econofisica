#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include "resultsManager.h"
// #include "/home/sebastiano/Scrivania/airoldi/librerie/funzioni/struct.h"

using namespace std;

void resultsManager::Set_structs_value( input_market_data &x, input_option_data &y, input_mc_data &z, std::string file) {
  vector<string> data_vector;
  ifstream myfile;
  myfile.open(file.c_str());

    if (myfile.is_open()) {
      std::cout << "file is open" << '\n';
      string line;
      while (getline(myfile, line))

        if (line[0] != '#')

          data_vector.push_back(line);

    } else std::cout << "file is not open " << '\n';

    //market data
    x.prezzo_iniziale = stod(data_vector[0]);
    x.risk_free_rate  = stod(data_vector[1]);
    x.volatility      = stod(data_vector[2]);
    //option data
    y.option_type     = stod(data_vector[3]);
    y.numero_steps    = stoi(data_vector[4]);
    y.delta_time      = stod(data_vector[5]);
    y.time_to_maturity= stod(data_vector[6]);
    y.strike_price    = stod(data_vector[7]);
    y.B               = stod(data_vector[8]);
    y.K               = stod(data_vector[9]);
    y.N               = stod(data_vector[10]);
    //montecarlo data
    z.N_simulazioni   = stoi(data_vector[11]);
    z.N_tb            = stoi(data_vector[12]);
    z.N_b             = stoi(data_vector[13]);

  myfile.close();
  std::cout << "file has been closed" << '\n';

}

void resultsManager::Set_output_file(string file) {

  ofstream myfile;
  myfile.open(file.c_str());

  if (myfile.is_open()) {
    std::cout << "file is open " << '\n';
  }

}
