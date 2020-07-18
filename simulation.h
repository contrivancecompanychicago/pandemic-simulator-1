#ifndef SIMULATION_H
#define SIMULATION_H

//setting max size of area
#define MAX_X 1000
#define MAX_Y 1000

//Number of people in the simulation
#define NUM_OF_PEOPLE 500
//Max speed of person
#define MAX_SPEED 50

//Number of popular places (must be greater than 0)
#define POPULAR_PLACES 20

//Chance of infection upon contact
#define INFECTION_CHANCE 0.20

//Maximum number of hours the infection lasts for
//Randomize in the future
#define MAX_INFECTION_DURATION 168

//The distance a person has to be from an infected individual in order to catch the pathogen
#define INFECTION_RADIUS 2

//Chance that person is social is social distancing
#define SOCIAL_DISTANCING_CHANCE 0.65

//Fatality rate
#define FATALITY_RATE 0.1

//Maximum amountt of time a person can spend in a popular place
#define MAX_TIME_AT_POPULAR_PLACE 3

//Maximum amount of time a person can spend at home
#define MAX_TIME_AT_HOME 20

//Number of cases at the start of the simulation
#define NUMBER_OF_CASES_UPON_START 1

//Defining color for different status types
#define VULNERABLE_COLOR Color::White
#define INFECTED_COLOR Color::Red
#define IMMUNE_COLOR Color::Blue
#define DEAD_COLOR Color::Green

namespace sim{
  //Disease status
  enum{IMMUNE, VULNERABLE, INFECTED, DEAD};
  //Location status
  enum{MOVING, AT_HOME, POPULAR_PLACE};
}
#endif
