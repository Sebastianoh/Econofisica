#include <iostream>
#include <cmath>
#include <cstdlib>
#include "funzioni.h"
#include "rng.h"
#include "rng.cu"
//le global non posso definirle nelle classi

int main() {

unsigned s1 = 0;
unsigned s2 = 0;
unsigned s3 = 0;
unsigned s4 = 0;

random_seed_generator(s1,s2,s3,s4);

rng random_number_generator(s1,s2,s3,s4);

//HO FATTO MOLTE PROVE: RIESCO A GENERARE NUMERI UNIFORMI E GAUSSIANI
//INOLTRE SONO DIVERSI OGNI VOLTA CHE LI GENERO

// COSA MANCA? DA UNA PARTE L'IMPLEMENTAZIONE IN C++ DEGLI STEP SUCCESSIVI
// DALL'ALTRA, APPENA LCM SARA' UP, PROVEREMO L'IMPLEMENTAZIONE IN CUDA


return 0;
}
