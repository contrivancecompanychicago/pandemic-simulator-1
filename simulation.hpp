#ifndef SIMULATION_HPP
#define SIMULATION_HPP

//setting max size of area
#define MAX_X 5000
#define MAX_Y 5000

//Number of people in the simulation
#define NUM_OF_PEOPLE 1000
//Max speed of person
#define MAX_SPEED 950

//Number of popular places
#define POPULAR_PLACES 13

namespace sim{
  enum{IMMUNE, VULNERABLE, INFECTED, DEAD};
}
#endif
