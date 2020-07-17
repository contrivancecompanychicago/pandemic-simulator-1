#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "person.hpp"
#include "simulation.h"
#include "popularplace.hpp"
#include <SFML/Graphics.hpp>

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
  CircleShape* SFMLPopularPlaces = new CircleShape[POPULAR_PLACES];
  Font helvetica_neue;
  helvetica_neue.loadFromFile("./fonts/HelveticaNeueLt.ttf");
  Text starttext;
  starttext.setString("Press space to begin");
  starttext.setCharacterSize(100.f);
  starttext.setFillColor(Color::White);
  starttext.setPosition(Vector2<float>(50.f, MAX_Y/2-100));
  starttext.setFont(helvetica_neue);
  //Initializing all of the objects
  Person* people[NUM_OF_PEOPLE];
  std::vector<Person*> infectedPeople;
  std::vector<Person*> vulnerablePeople;
  std::vector<Person*> tempPeople;
  srand(time(NULL));
  FILE* file = fopen("data.csv", "w");
  //Initializing people
  int i;
  bool stop = false, paused = true;
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
    SFMLPopularPlaces[i] = CircleShape(20.f);
    SFMLPopularPlaces[i].setPointCount(3);
    SFMLPopularPlaces[i].setFillColor(Color(255, 242, 0, 100));
    SFMLPopularPlaces[i].setPosition(Vector2<float>(PopularPlace::places[i].location->getX()-15, PopularPlace::places[i].location->getY()-15));
  }
  //The simulation
  int totalCases = NUMBER_OF_CASES_UPON_START;
  int activeCases = NUMBER_OF_CASES_UPON_START;
  int deaths = 0;
  int recoveries = 0;
  int hourNumber = 1;
  int status, x;
  window.draw(starttext);
  window.display();
  while(window.isOpen()){
    Event event;
    if(!stop){
      do{
        while(window.pollEvent(event)){
          switch(event.type){
            case Event::Closed:
            fclose(file);
            goto final;
            window.close();
            case Event::KeyPressed:
            if(event.key.code == Keyboard::Space){
              if(!paused){
                paused = true;
              } else{
                paused = false;
              }
            }
          }
        }
        if(!paused){
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
          for(i=0;i<POPULAR_PLACES;i++){
            window.draw(SFMLPopularPlaces[i]);
          }
          window.display();
          hourNumber++;
          logHour(file, totalCases, activeCases, deaths, recoveries);
          std::cout << "Total Cases: " << totalCases  << " Active Cases: " << activeCases << " Deaths: " << deaths << " Recoveries: " << recoveries <<" Hour:" <<  hourNumber << std::endl;
          stop = true;
        }
      } while(activeCases != 0);
    } else{
      while(window.pollEvent(event)){
        switch(event.type){
          case Event::Closed:
          fclose(file);
          final:
          window.close();
        }
      }
    }
  }
  fclose(file);
}

int main(){
  simulation();
  return 0;
}
