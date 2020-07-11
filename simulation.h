#ifndef SIMULATION_H
#define SIMULATION_H

//setting max size of area
#define MAX_X 100000
#define MAX_Y 100000

//Number of people in the simulation
#define NUM_OF_PEOPLE 15000
//Max speed of person
#define MAX_SPEED 950

//Number of popular places
#define POPULAR_PLACES 100

//Chance of infection upon contact
#define INFECTION_CHANCE 0.45

//Number of hours the infection lasts for
//Randomize in the future
#define INFECTION_DURATION 96

//The distance a person has to be from an infected individual in order to catch the pathogen
#define INFECTION_RADIUS 2

//Chance that person is social is social distancing
#define SOCIAL_DISTANCING_CHANCE 0.65

//Fatality rate
#define FATALITY_RATE 0.1

//Maximum amountt of time a person can spend in a popular place
#define MAX_TIME_AT_POPULAR_PLACE 4

//Maximum amount of time a person can spend at home
#define MAX_TIME_AT_HOME 16

//Number of cases at the start of the simulation
#define NUMBER_OF_CASES_UPON_START 1

namespace sim{
  //Disease status
  enum{IMMUNE, VULNERABLE, INFECTED, DEAD};
  //Location status
  enum{MOVING, AT_HOME, POPULAR_PLACE};
}
#endif
