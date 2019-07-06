NVCC=nvcc

CUDAFLAGS= -arch=sm_30

OPT= -g -G

RM=/bin/rm -f
all: main

main: main.o processo_stocastico.o rng.o
	${NVCC} $[OPT] -o main main.o processo_stocastico.o rng.o
processo_stocastico.o: processo_stocastico.h processo_stocastico.cu
