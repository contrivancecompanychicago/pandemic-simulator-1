#include "person.hpp"
#include "simulation.h"
#include "popularplace.hpp"
#include <ctime>
#include <cmath>
#include <cstdlib>

namespace sim{
  Person::Person()
    : status(VULNERABLE), elapsedTimeSinceInfection(0),
    locationStatus(AT_HOME), timeSinceArrival(0),
    timeTillDeparture(0)
  {
    home = new Place();
    location = new Location(home->location->getX(), home->location->getY());
    srand(time(NULL));
    if(fmod(rand(), (100/(SOCIAL_DISTANCING_CHANCE*100)+1)) == 0){
      isSocialDistancing = true;
    } else{
      isSocialDistancing = false;
    }
    targetLocation = home->location;
  }
  Person::~Person(){
    delete home;
    delete location;
    delete targetLocation;
  }
  bool Person::on_contact(){
    if(status == VULNERABLE){
      srand(time(NULL));
      if(fmod(rand(), (100/(INFECTION_CHANCE*100))+1) == 0){
        status = INFECTED;
        return true;
      } else{
        return false;
      }
    } else{
      return false;
    }
  }
  void Person::action(){
    if(status != DEAD){
      if(locationStatus == MOVING){
        if(location->move(*targetLocation, MAX_SPEED)){ //Randomize max speed later for better simulation
          srand(time(NULL));
          if(location->atLocation(*(home->location))){
            locationStatus =  AT_HOME;
            timeTillDeparture = rand()%(MAX_TIME_AT_HOME+1);
          } else{
            locationStatus = POPULAR_PLACE;
            timeTillDeparture = rand()%(MAX_TIME_AT_POPULAR_PLACE+1);
          }
        }
      } else if(locationStatus == AT_HOME){
        if(timeSinceArrival >= timeTillDeparture){
          timeSinceArrival = 0;
          timeTillDeparture = 0;
          locationStatus = MOVING;
          srand(time(NULL));
          targetLocation = PopularPlace::places[rand()%(POPULAR_PLACES+1)]->location;
          location->move(*targetLocation, MAX_SPEED);
        } else{
          timeSinceArrival++;
        }
      } else{
        if(timeSinceArrival >= timeTillDeparture){
          timeSinceArrival = 0;
          timeTillDeparture = 0;
          locationStatus = MOVING;
          targetLocation = home->location;
          location->move(*targetLocation, MAX_SPEED);
        } else{
          timeSinceArrival++;
        }
      }
    }
  }

  int Person::addHour(){
    if(status == INFECTED){
      elapsedTimeSinceInfection++;
      if(elapsedTimeSinceInfection == INFECTION_DURATION){
        srand(time(NULL));
        if(rand()%(((int)(100/(FATALITY_RATE*100)))+1) == 0){
          status = DEAD;
          action();
          return DEAD;
        } else{
          status = IMMUNE;
          action();
          return IMMUNE;
        }
      } else{
        action();
        return INFECTED;
      }
    } else if(status == VULNERABLE){
      action();
      return VULNERABLE;
    } else if(status == DEAD){
      action();
      return DEAD;
    } else{
      action();
      return IMMUNE;
    }
    return -1;
  }
  Location* Person::getLocation() const{
    return location;
  }
}
