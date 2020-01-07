#ifndef __resultsManager_h__
#define __resultsManager_h__

#include <string>
#include "resultsManager.cu"

class resultsManager {
  private:
  //vedrò cosa mi serve
  // nome input e output files?
    // string myfile_input;
    // string myfile_output;

  public:
// COSA DEVE FARE STA ROBA?
  //  I-O DA FILE
    __host__ resultsManager();

    __host__ void Set_input_file(string file);
    __host__ void Set_output_file(string file);

// devo prendere i miei dati da file e caricarli nelle strutture
// void set_structures? prende da file i valori e li mette, ma come?

    // __host__

};

#endif
