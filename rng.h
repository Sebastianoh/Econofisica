 #ifndef __rng_h__
 #define __rng_h__
 // #include "funzioni.h"

class rng {
  private:

    unsigned m_s1, m_s2, m_s3, m_s4;
    double m_gauss1, m_gauss2 ; //variabili private che mi servono per i numeri gauss

  public:
    rng();
    rng(unsigned, unsigned, unsigned, unsigned);  //constructor
    ~rng(); //destructor

  /*  __device__ */ unsigned TauStep (unsigned &seed, int k1, int k2, int k3, unsigned M);
  /*  __device__*/ unsigned LNG     (unsigned &seed, unsigned a, unsigned b);
    /*__device__*/ double hybrid();  //(unsigned s1, unsigned s2, unsigned s3, unsigned s4);
                  void BoxMuller (double &u, double &v);
                  double Get_uniform();

                    double Get_gauss();


};

#endif
