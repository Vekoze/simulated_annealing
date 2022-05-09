CC = g++
LFLAGS = -lm -Wall
OBJ = simulated_annealing.o utils.o
EXEC_NAME = simulated_annealing

all : delete $(EXEC_NAME) clean

delete : 
	@rm -f $(EXEC_NAME)

clean :
	@rm -f *.o

$(EXEC_NAME) : $(OBJ)
	@$(CC) -o $(EXEC_NAME) $(OBJ) $(LFLAGS)

simulated_annealing.o : simulated_annealing.cpp
	@$(CC) -c simulated_annealing.cpp

utils.o : utils.cpp utils.hpp
	@$(CC) -c utils.cpp