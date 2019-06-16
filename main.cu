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

// std::cout << "seeds: " << s1 << ", " << s2 << ", " << s3 << ", " << s4 <<'\n';

unsigned a = 0;

rng random_number_generator(s1,s2,s3,s4);

a = random_number_generator.hybrid();

std::cout << "a:" << a << '\n';


return 0;
}
