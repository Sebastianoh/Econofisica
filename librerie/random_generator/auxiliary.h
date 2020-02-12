#ifndef __auxiliary_h__
#define __auxiliary_h__

class auxiliary {

public:

  __device__ __host__ auxiliary();
  __device__ __host__ auxiliary(const unsigned int);

  __device__ __host__ unsigned Tau();
  __device__ __host__ unsigned Get_unsigned_int();

private:

  unsigned _seed;
};

#endif
