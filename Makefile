MAKEFLAGS += --silent

CC = g++
SRC = src/*.cpp
OBJ = bin/*.o
DEPS = bin/deps
INCLUDE = include
OUTFILE = ping

CXXFLAGS += -std=c++20
CXXFLAGS += -I$(INCLUDE)
CXXFLAGS += -Wall

_main: depend build
build: $(SRC)
	$(CC) -c $(CXXFLAGS) $^
	mkdir -p bin && mv *.o bin/
	$(CC) -o $(OUTFILE) $(OBJ)

depend:
	$(CC) -MM -I$(INCLUDE) $(SRC) > $(DEPS)

-include $(DEPS)


run: _run cleanall
_run: build
	./$(OUTFILE)

.PHONY: clean cleanall
clean:
	rm -f *.o

cleanall: clean
	rm -f $(OUTFILE)