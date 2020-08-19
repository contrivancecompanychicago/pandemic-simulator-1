#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include "person.hpp"
#include "simulation.h"
#include "popularplace.hpp"

extern "C"{
  void logHour(FILE* file, int totalCases, int activeCases, int deaths, int recoveries);
}

void simulation(bool writeData){
  using namespace sim;
  using namespace sf;
  int i;
  //SFML initialization
  RenderWindow window(VideoMode(1000, 1100), "Pandemic Simulator", Style::Close | Style::Titlebar);
  window.setFramerateLimit(60);
  CircleShape* SFMLPeople = new CircleShape[NUM_OF_PEOPLE];
  CircleShape* SFMLPopularPlaces = new CircleShape[POPULAR_PLACES];
  Font helvetica_neue;
  View mainView(Vector2<float>(500.f, 550.f), Vector2<float>(1000.f, 1100.f));
  View statView(Vector2<float>(550.f, 55.f), Vector2<float>(1100.f, 90.f));
  mainView.setViewport(Rect<float>(0.f,0.f, 1.f, 0.9f));
  statView.setViewport(Rect<float>(0.f,0.9f, 1.f, 0.1f));
  helvetica_neue.loadFromFile("./fonts/HelveticaNeueLt.ttf");
  //Text for SFML
  Text starttext, SFML_vulnerable, SFML_infected, SFML_dead, SFML_immune;
  Text* stattext[4] = {&SFML_vulnerable, &SFML_infected, &SFML_dead, &SFML_immune};
  //Text for stats
  SFML_vulnerable.setFillColor(VULNERABLE_COLOR);
  SFML_infected.setFillColor(INFECTED_COLOR);
  SFML_dead.setFillColor(DEAD_COLOR);
  SFML_immune.setFillColor(IMMUNE_COLOR);
  SFML_vulnerable.setString(std::to_string(NUM_OF_PEOPLE-NUMBER_OF_CASES_UPON_START));
  SFML_infected.setString(std::to_string(NUMBER_OF_CASES_UPON_START));
  SFML_dead.setString("0");
  SFML_immune.setString("0");
  { //Scope for positioncounter variable
    float positioncounter = 0;
    for(i=0;i<4;i++){
      stattext[i]->setFont(helvetica_neue);
      stattext[i]->setCharacterSize(75.f);
      stattext[i]->setPosition(Vector2<float>(5.f+positioncounter , 12.5f));
      positioncounter+= 75.f*((std::to_string(NUM_OF_PEOPLE)).length());
    }
  }
  //Text for main menu
  starttext.setString("Press space to begin");
  starttext.setCharacterSize(100.f);
  starttext.setFillColor(Color::White);
  starttext.setPosition(Vector2<float>(50.f, 400.f));
  starttext.setFont(helvetica_neue);
  //Initializing all of the objects
  Person* people[NUM_OF_PEOPLE];
  std::vector<Person*> infectedPeople;
  std::vector<Person*> vulnerablePeople;
  std::vector<Person*> tempPeople;
  srand(time(NULL));
  FILE* file = NULL;
  if(writeData){
    file = fopen("data.csv", "w");
  }
  //Initializing people
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
        if(Keyboard::isKeyPressed(Keyboard::Left)){
          statView.setCenter(Vector2<float>(statView.getCenter().x-10, statView.getCenter().y));
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
          statView.setCenter(Vector2<float>(statView.getCenter().x+10, statView.getCenter().y));
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
          mainView.setCenter(Vector2<float>(mainView.getCenter().x, mainView.getCenter().y-25));
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
          mainView.setCenter(Vector2<float>(mainView.getCenter().x-25, mainView.getCenter().y));
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
          mainView.setCenter(Vector2<float>(mainView.getCenter().x, mainView.getCenter().y+25));
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
          mainView.setCenter(Vector2<float>(mainView.getCenter().x+25, mainView.getCenter().y));
        }
        window.setView(mainView);
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
          SFML_vulnerable.setString(std::to_string(NUM_OF_PEOPLE-totalCases));
          SFML_infected.setString(std::to_string(activeCases));
          SFML_dead.setString(std::to_string(deaths));
          SFML_immune.setString(std::to_string(recoveries));
          window.setView(statView);
          for(i=0;i<4;i++){
            window.draw(*(stattext[i]));
          }
          window.display();
          hourNumber++;
          if(writeData){
            logHour(file, totalCases, activeCases, deaths, recoveries);
          }
          //std::cout << "Total Cases: " << totalCases  << " Active Cases: " << activeCases << " Deaths: " << deaths << " Recoveries: " << recoveries <<" Hour:" <<  hourNumber << std::endl;
          stop = true;
        }
      } while(activeCases != 0);
    } else{
      while(window.pollEvent(event)){
        switch(event.type){
          case Event::Closed:
          if(writeData){
            fclose(file);
          }
          final:
          window.close();
        }
      }
    }
  }
  if(writeData){
    fclose(file);
  }
}

int main(int argc, char* argv[]){
  if(argc <= 1){
    simulation(false);
  } else{
    int i;
    for(i=0;i<argc;i++){
      if(std::strcmp(argv[i], "-k") == 0){
        std::cout<<"White Dot - Vulnerable\nRed Dot - Infected\nBlue Dot - Immune/Recovered\nGreen Dot - Dead\nYellow Triangle - Popular Place"<<std::endl;
      } else if(std::strcmp(argv[i], "-h") == 0){
        std::cout<<"Help\nArg - Function\n\'-k\' - Key\n\'-d\' - Write data into \'data.csv\' file\n\'-c\' - Console version"<<std::endl;
      } else if(strcmp(argv[i], "-d") == 0){
        simulation(true);
      } else if(strcmp(argv[i], "-c") == 0){
        std::cout<<"Coming soon"<<std::endl;
      }
    }
  }
  return 0;
}
