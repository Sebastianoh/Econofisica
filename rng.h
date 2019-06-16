 #ifndef __rng_h__
 #define __rng_h__
 // #include "funzioni.h"

class rng {
  private:

    unsigned m_s1, m_s2, m_s3, m_s4;

  public:
    rng();
    rng (unsigned s1, unsigned s2, unsigned s3, unsigned s4);  //constructor
    ~rng (); //destructor

    // void first_generator(); //generatore dei primi 4 seed

    //metodi per accedere ai seed dopo averli generati

     unsigned Get_uniform(); //{return m_s1;}
     unsigned Get_gauss();   //{return m_s2;}
    // unsigned Get_s3() {return m_s3;}
    // unsigned Get_s4() {return m_s4;}

    __device__ unsigned TauStep (unsigned seed, int k1, int k2, int k3, unsigned M);
    __device__ unsigned LNG     (unsigned seed, unsigned a, unsigned b);
    __device__ unsigned hybrid();  //(unsigned s1, unsigned s2, unsigned s3, unsigned s4);
  //questa mi riempie un vettore di n numeri casuali
    // __global__ void combined_generator (unsigned * r);

};

#endif
