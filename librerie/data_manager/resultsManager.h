#ifndef __resultsManager_h__
#define __resultsManager_h__

#include <string>
#include <iostream>
#include "../funzioni/struct.h"

// #include "resultsManager.cu"

class resultsManager {
  private:
  /*  // private market data
    double m_prezzo_iniziale; //prezzo azione a tempo iniziale
  	double m_risk_free_rate;
  	double m_volatility;

    // private option data
    float  m_option_type;  //0-1-2
  	int    m_numero_steps; //il numero di steps son già le date di fixing
  	double m_delta_time;
  	double m_time_to_maturity;
    double m_strike_price; //strike price
  	double m_B;
  	double m_K;
  	double m_N;  //EUR

    // private mc data

  	int m_N_simulazioni;
  	int m_N_tb; //numero thread per blocco
  	int m_N_b; // numero blocchi
*/
  public:

    resultsManager() {};

    void Set_output_file(std::string file);
                         //market data //option data //mc_data
    void Set_structs_value( input_market_data &x, input_option_data &y, input_mc_data &z, std::string file);//le varie strutture? i guess)

};

#endif
