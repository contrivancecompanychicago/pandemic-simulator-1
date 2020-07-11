#ifndef SIMULATION_H
#define SIMULATION_H

//setting max size of area
#define MAX_X 5000
#define MAX_Y 5000

//Number of people in the simulation
#define NUM_OF_PEOPLE 1000
//Max speed of person
#define MAX_SPEED 950

//Number of popular places
#define POPULAR_PLACES 13

//Chance of infection upon contact
#define INFECTION_CHANCE 0.5

//Number of hours the infection lasts for
#define INFECTION_DURATION 336

//The distance a person has to be from an infected individual in order to catch the pathogen
#define INFECTION_RADIUS 3

//Chance that person is social is social distancing
#define SOCIAL_DISTANCING_CHANCE 0.45

//Fatality rate
#define FATALITY_RATE 0.1

namespace sim{
  //Disease status
  enum{IMMUNE, VULNERABLE, INFECTED, DEAD};
  //Location status
  enum{MOVING, AT_HOME, POPULAR_PLACE};
}
#endif
