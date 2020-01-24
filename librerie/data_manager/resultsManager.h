#ifndef __resultsManager_h__
#define __resultsManager_h__

#include <string>
#include <iostream>
#include "../funzioni/struct.h"

// #include "resultsManager.cu"

class resultsManager {
  public:

    resultsManager() {};

    void Set_output_file(std::string file);
                         //market data //option data //mc_data
    void Set_structs_value( input_market_data &x, input_option_data &y, input_mc_data &z, input_gpu_data &w, std::string file);//le varie strutture? i guess)

};

#endif
