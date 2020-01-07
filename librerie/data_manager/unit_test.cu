#include <string>
#include <iostream>
#include "resultsManager.h"

using namespace std;

int main() {

  string input_file("input_file.dat");
  string output_file("output_file.dat");

  resultsManager rsm;

  rsm.Set_input_file(input_file);
  rsm.Set_output_file(output_file);

}
