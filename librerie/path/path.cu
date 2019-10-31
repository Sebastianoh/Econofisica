#include <iostream>
#include <cmath>
#include <cstdlib>
#include "path.h"

__device__ __host__ path::path() {

  m_volatility      = 0;
  m_risk_free_rate  = 0;
  m_prezzo_iniziale = 0;

  m_price           = 0;

  m_option_type     = 0;
  m_numero_steps    = 0;
  m_delta_time      = 0;
  m_time_to_maturity= 0;
  m_strike_price    = 0;

  m_payoff = 0;

  m_B = 0;
  m_K = 0;
  m_N = 0;
  m_corridor = 0;

}



__device__ __host__ path::path(input_option_data option, input_market_data market) {

  m_volatility      = (market.volatility);
  m_risk_free_rate  = (market.risk_free_rate);
  m_prezzo_iniziale = (market.prezzo_iniziale);

  m_price           = market.prezzo_iniziale;

  m_option_type     = (option.option_type);
  m_numero_steps    = (option.numero_steps);
  m_delta_time      = (option.delta_time);
  m_time_to_maturity= (option.time_to_maturity);
  m_strike_price    = (option.strike_price);

  m_payoff = 0;

  m_B = (option.B);
  m_K = (option.K);
  m_N = (option.N);

  m_corridor = 0;
  // m_date_fixing = date_fixing;
}

// copy costructor

/*__device__ __host__ path::path(const path &path2) {
  m_p            = path2.m_p;
  volatility          = path2.volatility;
  risk_free_rate = path2.risk_free_rate;

  m_strike_price            = path2.m_strike_price;
  dt             = path2.dt;
  m_n_steps      = path2.m_n_steps;

}*/



//destructor
__device__ __host__ path::~path() {

  } ;

__device__ __host__ double path::GetPrice() {
  return m_price;
}

__device__ __host__ void path::corridor_controller(double prezzo1, double prezzo2) {

  double value_to_be_checked = fabs((1/sqrt(m_delta_time))*log(prezzo2/prezzo1));
  double barriera            = m_B * m_volatility;

    if (value_to_be_checked < barriera) {

      m_corridor ++ ;

    }

}

__device__ __host__ void path::eulero(double gauss) {

    double price_i;
    price_i = m_price * (1 + m_risk_free_rate*m_delta_time + m_volatility*sqrt(m_delta_time)*gauss);

      if (m_option_type == 2) {
        corridor_controller(price_i, m_price);
      }

    m_price = price_i;

    // check negative price
}





  //payoff

__device__ __host__ void path::payoff_evaluator() {

  //  OPTION TIPES: f(orward) - p(lain vanilla) - c(orridor)

  if (m_option_type == 0) {

    m_payoff = m_price;

  }

  if (m_option_type == 1) {
    // double payoff = 0;
    m_payoff = max(m_price - m_strike_price, 0.);
    // return payoff;
  }

  if (m_option_type == 2) {

    m_payoff = m_N *(max((1/m_numero_steps)*m_corridor - m_K, 0.));

  }
  // else m_payoff = -1000;

}





__device__ __host__ double path::Get_payoff() {

  return m_payoff;

}
