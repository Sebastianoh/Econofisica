TARGETS=resultsManager.o unit_test.o

NVCC=nvcc -std=c++11

ECHO=/bin/echo

RM=/bin/rm -f

all: $(TARGETS)
	$(NVCC) $(TARGETS) -o unit_test.x

%.o: %.cu
	 $(NVCC) -dc $< -o $@
	 
run:
	make	
	./unit_test.x

clean:
	@echo "cleaning..."
	rm -f *.x *.o
	
	
