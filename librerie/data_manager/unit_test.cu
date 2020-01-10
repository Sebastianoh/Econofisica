#include <string>
#include <iostream>
#include "resultsManager.h"
// #include "/home/sebastiano/Scrivania/airoldi/librerie/funzioni/struct.h"

using namespace std;

int main() {

  input_mc_data mc_data;
  input_market_data market_data;
  input_option_data option_data;

  string input_file("input_file.dat");
  string output_file("output_file.dat");

  resultsManager rsm;

  //market data //option data //mc_data
  rsm.Set_structs_value(market_data, option_data, mc_data, input_file);

  // rsm.Set_output_file(output_file);
  std::cout << "test data" << option_data.strike_price << '\n';
  return 0;

}
