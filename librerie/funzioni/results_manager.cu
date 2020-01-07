#include <iostream>
#include <fstream>
#include "resultsManager.h"

__host__ resultsManager::resultsManager() {};

__host__ void resultsManager::Set_input_file(string file) {

  ifstream myfile;
  myfile.open(file);

  if (myfile.is_open()) {
    std::cout << " input file is open  " << '\n';
  }
}

__host__ void resultsManager::Set_output_file(string file) {

  ofstream myfile;
  myfile.open(file)

  if (myfile.is_open()) {
    std::cout << " output file is open  " << '\n';
  }

}
