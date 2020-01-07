#include <string>
#include <fstream>
#include <iostream>
#include "resultsManager.h"

using namespace std;

void resultsManager::Set_input_file(string file) {

  ifstream myfile;
  myfile.open(file);

    if (myfile.is_open()) {
      std::cout << "file is open" << '\n';
    }

}

void resultsManager::Set_output_file(string file) {

  ofstream myfile;
  myfile.open(file);

  if (myfile.is_open()) {
    std::cout << "file is open " << '\n';
  }

}
