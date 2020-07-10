main: location.o simulation.hpp main.cpp
	g++ -o main main.cpp location.o
	
location.o: location.cpp location.hpp simulation.hpp
	g++ -c location.cpp

clean:
	rm location.o

removeMain:
	rm main
