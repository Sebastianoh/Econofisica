//#### STRUTTURE DI DATI ####
#ifndef __struct_h__
#define __struct_h__

struct input_market_data {
	double S_0; //prezzo azione a tempo iniziale
	double risk_free_rate;
	double sigma;
};

struct input_option_data {
	double E; //strike price
	double delta_t;
	double num_intervals;
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
