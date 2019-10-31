//#### STRUTTURE DI DATI ####
#ifndef __struct_h__
#define __struct_h__

struct input_market_data {

	double prezzo_iniziale; //prezzo azione a tempo iniziale
	double risk_free_rate;
	double volatility;
	// int date_fixing;

};

struct input_option_data {

	float  option_type;  //0-1-2
	int    numero_steps; //il numero di steps son già le date di fixing
	double delta_time;
	double time_to_maturity;
	double strike_price; //strike price

	//se è corridor

	double B;
	double K;
	double N;  //EUR
	// double T;  years
	// double m;  date di fixing
};

struct input_mc_data {

	int N_simulazioni;
	int N_tb; //numero thread per blocco
	int N_b; // numero blocchi

};

struct output_mc_data {

	double price_mc;
	double err_mc;
	double err_bs; //errore rispetto al risultato esatto
	int tick; //tempo di calcolo in ms

};


#endif
