#include "person.hpp"
#include "simulation.h"
#include "popularplace.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>

void simulation(){
  using namespace sim;
  //Initializing all of the objects
  Person* people[NUM_OF_PEOPLE];
  std::vector<Person*> infectedPeople;
  std::vector<Person*> vulnerablePeople;
  std::vector<Person*> tempPeople;
  srand(time(NULL));
  //Initializing people
  int i;
  for(i=0;i<NUM_OF_PEOPLE; i++){
    people[i] = new Person();
    if(i < NUMBER_OF_CASES_UPON_START){
      people[i]->setStatus(INFECTED);
      people[i]->id = infectedPeople.size();
      infectedPeople.push_back(people[i]);
    } else{
      people[i]->id =vulnerablePeople.size();
      vulnerablePeople.push_back(people[i]);
    }
  }
  //Initializing popular places
  for(i=0;i<POPULAR_PLACES;i++){
    PopularPlace();
  }
  //The simulation
  int totalCases = NUMBER_OF_CASES_UPON_START;
  int activeCases = NUMBER_OF_CASES_UPON_START;
  int deaths = 0;
  int recoveries = 0;
  int hourNumber = 1;
  int status, x;
  do{
    for(i=0; i<infectedPeople.size();i++){
      if(infectedPeople[i] != NULL){
        for(x=0;x<vulnerablePeople.size();x++){
          if(vulnerablePeople[x] != NULL){
            if(infectedPeople[i]->getLocation()->getDistance(*(vulnerablePeople[x]->getLocation())) <= INFECTION_RADIUS){
              if(vulnerablePeople[x]->on_contact() == true){
                vulnerablePeople[x]->setStatus(INFECTED);
                totalCases++;
                activeCases++;
                tempPeople.push_back(vulnerablePeople[x]);
                vulnerablePeople[x] = NULL;
              }
            }
          }
        }
      }
    }
    for(i=0;i<tempPeople.size();i++){
      tempPeople[i]->id = infectedPeople.size();
      infectedPeople.push_back(tempPeople[i]);
    }
    tempPeople.clear();
    for(i=0;i<NUM_OF_PEOPLE;i++){
      status = people[i]->addHour();
      if(status == IMMUNE){
        activeCases--;
        recoveries++;
        infectedPeople[people[i]->id] = NULL;
      } else if(status == DEAD){
        activeCases--;
        deaths++;
        infectedPeople[people[i]->id] = NULL;
      }
    }
    //Need to add to totals
    hourNumber++;
  } while(activeCases != 0);
  std::cout << "Total Cases: " << totalCases  << " Active Cases: " << activeCases << " Deaths: " << deaths << " Recoveries: " << recoveries <<" Hour:" <<  hourNumber << std::endl;
}

int main(){
  simulation();
  return 0;
}
