TARGETS=./random_generator/rng.o ./path/path.o ./statistica/statistica.o ./data_manager/resultsManager.o main.o

NVCC=nvcc -std=c++11

ECHO=/bin/echo

RM=/bin/rm -f

all: $(TARGETS)
	$(NVCC) $(TARGETS) -o main.x

%.o: %.cu
	 $(NVCC) -dc $< -o $@

run:
	make
	./main.x

clean:
	@echo "cleaning..."
	$(RM) *.x *.o
	$(RM) ./*/*.x ./*/*.o
