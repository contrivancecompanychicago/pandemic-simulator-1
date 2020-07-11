main: location.o simulation.h main.cpp place.o popularplace.o
	g++ -o main main.cpp location.o place.o popularplace.o

location.o: location.cpp location.hpp simulation.h
	g++ -c location.cpp

place.o: place.hpp place.cpp
	g++ -c place.cpp

popularplace.o: place.hpp place.cpp simulation.h popularplace.hpp popularplace.cpp
	g++ -c popularplace.cpp

person.o: person.cpp person.hpp location.hpp simulation.h place.hpp place.cpp location.cpp
	g++ -c person.cpp
clean:
	rm *.o
