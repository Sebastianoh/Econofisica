#include "./path/path.h"
#include "./funzioni/struct.h"
#include "./funzioni/funzioni.h"
#include "./statistica/statistica.h"
#include "./random_generator/rng.cuh"
#include "./data_manager/resultsManager.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  //creo le struct da caricare
  input_mc_data mc_data;
  input_market_data market_data;
  input_option_data option_data;

  string input_file("./data_manager/input_file.dat");
  string output_file("./data_manager/output_file.dat");

  resultsManager rsm;

  rsm.Set_structs_value(market_data, option_data, mc_data, input_file);

  output_statistica *output_cpu = new output_statistica[mc_data.N_simulazioni];
  output_statistica *output_gpu = new output_statistica[mc_data.N_simulazioni];

  std::cout << "begin CPU simulation ...." << '\n';
  CPU_caller(market_data, option_data, mc_data, output_cpu);
  std::cout << "CPU simulation ended ...." << '\n';

  delete[] output_cpu;  

  std::cout << "begin GPU simulation ...." << '\n';

  global_caller(market_data, option_data, mc_data, output_gpu);

  return 0;

}
