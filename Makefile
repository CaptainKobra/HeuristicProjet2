CXX=g++
CXXFLAGS= -Wall -Wextra -pedantic
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=PFSP

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)


