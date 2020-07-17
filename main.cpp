#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "person.hpp"
#include "simulation.h"
#include "popularplace.hpp"
#include <SFML/Graphics.hpp>
#include <unistd.h>

extern "C"{
  void logHour(FILE* file, int totalCases, int activeCases, int deaths, int recoveries);
}

void simulation(){
  using namespace sim;
  using namespace sf;
  //SFML initialization
  RenderWindow window(VideoMode(MAX_X, MAX_Y), "Pandemic Simulator", Style::Close | Style::Titlebar);
  window.setFramerateLimit(60);
  CircleShape* SFMLPeople = new CircleShape[NUM_OF_PEOPLE];
  //Initializing all of the objects
  Person* people[NUM_OF_PEOPLE];
  std::vector<Person*> infectedPeople;
  std::vector<Person*> vulnerablePeople;
  std::vector<Person*> tempPeople;
  srand(time(NULL));
  FILE* file = fopen("data.csv", "w");
  //Initializing people
  int i;
  bool stop = false;
  for(i=0;i<NUM_OF_PEOPLE; i++){
    people[i] = new Person();
    if(i < NUMBER_OF_CASES_UPON_START){
      people[i]->setStatus(INFECTED);
      people[i]->id = infectedPeople.size();
      infectedPeople.push_back(people[i]);
      SFMLPeople[i] = CircleShape(5.f);
      SFMLPeople[i].setFillColor(INFECTED_COLOR);
    } else{
      people[i]->id =vulnerablePeople.size();
      vulnerablePeople.push_back(people[i]);
      SFMLPeople[i] = CircleShape(5.f);
      SFMLPeople[i].setFillColor(VULNERABLE_COLOR);
    }
  }
  //Initializing popular places
  for(i=0;i<POPULAR_PLACES;i++){
    PopularPlace place;
  }
  //The simulation
  int totalCases = NUMBER_OF_CASES_UPON_START;
  int activeCases = NUMBER_OF_CASES_UPON_START;
  int deaths = 0;
  int recoveries = 0;
  int hourNumber = 1;
  int status, x;
  while(window.isOpen()){
    Event event;
    while(window.pollEvent(event)){
      switch(event.type){
        case Event::Closed:
        fclose(file);
        window.close();
      }
    }
    if(!stop){
      do{
        for(i=0; i<infectedPeople.size();i++){
          if(infectedPeople[i] != NULL){
            for(x=0;x<vulnerablePeople.size();x++){
              if(vulnerablePeople[x] != NULL){
                if(vulnerablePeople[x]->getLocationStatus() != AT_HOME){
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
        }
        for(i=0;i<tempPeople.size();i++){
          tempPeople[i]->id = infectedPeople.size();
          infectedPeople.push_back(tempPeople[i]);
        }
        window.clear();
        tempPeople.clear();
        for(i=0;i<NUM_OF_PEOPLE;i++){
          status = people[i]->addHour();
          if(status == IMMUNE){
            activeCases--;
            recoveries++;
            infectedPeople[people[i]->id] = NULL;
            SFMLPeople[i].setFillColor(IMMUNE_COLOR);
          } else if(status == DEAD){
            activeCases--;
            deaths++;
            SFMLPeople[i].setFillColor(DEAD_COLOR);
            infectedPeople[people[i]->id] = NULL;
          } else if(status == INFECTED){
            SFMLPeople[i].setFillColor(INFECTED_COLOR);
          }
          SFMLPeople[i].setPosition(Vector2<float>(people[i]->getLocation()->getX(), people[i]->getLocation()->getY()));
          window.draw(SFMLPeople[i]);
        }
        window.display();
        hourNumber++;
        logHour(file, totalCases, activeCases, deaths, recoveries);
        std::cout << "Total Cases: " << totalCases  << " Active Cases: " << activeCases << " Deaths: " << deaths << " Recoveries: " << recoveries <<" Hour:" <<  hourNumber << std::endl;
        stop = true;
      } while(activeCases != 0);
    }
  }
  fclose(file);
}

int main(){
  simulation();
  return 0;
}
