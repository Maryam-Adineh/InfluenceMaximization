CC=g++
CFLAGS=-I.
DEPS = limit.h Graph.h IndependCascade.h DegreeDecrease.h NeighborsRemove.h

OBJ = Graph.o main.o DegreeDecrease.o IndependCascade.o NeighborsRemove.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

InfluenceMaximization: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
