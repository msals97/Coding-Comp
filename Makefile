CXX = g++
VARNAME = value
CXXFLAGS = -Wall -g

main: Functions.o MatInverse.o Polyfit.o RootFind.o LMSFit.o MassRadius.o
	$(CXX) $(CXXFLAGS) -o main Functions.o MatInverse.o Polyfit.o RootFind.o LMSFit.o MassRadius.o

Functions.o: Functions.h
	$(CXX) $(CXXFLAGS) -c Functions.cpp

MatInverse.o: Functions.h MatInverse.h
	$(CXX) $(CXXFLAGS) -c MatInverse.cpp

Polyfit.o: Functions.h MatInverse.h Polyfit.h
	$(CXX) $(CXXFLAGS) -c Polyfit.cpp

RootFind.o: Functions.h MatInverse.h Polyfit.h RootFind.h
	$(CXX) $(CXXFLAGS) -c RootFind.cpp

LMSFit.o: Functions.h MatInverse.h Polyfit.h RootFind.h
	$(CXX) $(CXXFLAGS) -c LMSFit.cpp

MassRadius.o: Functions.h MatInverse.h Polyfit.h RootFind.h
	$(CXX) $(CXXFLAGS) -c MassRadius.cpp

clean:
	rm -f main main.o Functions.o MatInverse.o Polyfit.o RootFind.o LMSFit.o MassRadius.o