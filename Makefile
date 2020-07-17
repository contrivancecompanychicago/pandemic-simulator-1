main: main.cpp simulation.h location.o place.o popularplace.o person.o data.o
	g++ -o main main.cpp *.o -I./include -lsfml-graphics -lsfml-window -lsfml-system

location.o: location.cpp location.hpp simulation.h
	g++ -c location.cpp

place.o: place.hpp place.cpp
	g++ -c place.cpp

popularplace.o: place.hpp place.cpp simulation.h popularplace.hpp popularplace.cpp
	g++ -c popularplace.cpp

person.o: person.cpp person.hpp location.hpp simulation.h place.hpp place.cpp location.cpp popularplace.o
	g++ -c person.cpp

data.o: data.c
	gcc -c data.c
clean:
	rm *.o
