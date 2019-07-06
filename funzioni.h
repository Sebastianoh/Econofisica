#include <iostream>
#include <cmath>
#include "struct.h"

void random_seed_generator(unsigned &s1, unsigned &s2, unsigned &s3, unsigned &s4) {

  srand(time(NULL));

  s1 = rand() % 1000000+128;
  s2 = rand() % 1000000+128;
  s3 = rand() % 1000000+128;
  s4 = rand() % 1000000+128;

}

void set_struct_values(input_market_data& b, input_option_data& a, input_mc_data & c) {

  a.E              = 100;
  a.delta_t        = 1;
  a.num_intervals  = 50;

  b.S_0            = 100; //prezzo azione a tempo iniziale
  b.risk_free_rate = 0.02;
  b.sigma          = 0.5;

  c.N_simulazioni = 15;
  c.N_tb = 20;
  c.N_b = 2;
}
