#include <iostream>
// #include "main.cu"
#include <cmath>

void random_seed_generator(unsigned &s1, unsigned &s2, unsigned &s3, unsigned &s4) {

  srand(time(NULL));

  s1 = rand() % 1000000+128;
  s2 = rand() % 1000000+128;
  s3 = rand() % 1000000+128;
  s4 = rand() % 1000000+128;

}
