#include "person.hpp"
#include "simulation.h"
#include <ctime>
#include <cmath>
#include <cstdlib>

namespace sim{
  Person::Person()
    : status(VULNERABLE), elapsedTimeSinceInfection(0), locationStatus(AT_HOME), timeSinceArrival(0)
  {
    home = new Place();
    location = new Location(home->location->getX(), home->location->getY());
    srand(time(NULL));
    if(fmod(rand(), 100/(SOCIAL_DISTANCING_CHANCE*100)) == 0){
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
      if(fmod(rand(), 100/(INFECTION_CHANCE*100)) == 0){
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
    //Use timeSinceArrival & targetLocation
    if(locationStatus == MOVING){
      //Handle person moving
    } else if(locationStatus == AT_HOME){
      //Handle person at home
    } else{
      //Handle person at popular place
    }
  }
  int Person::addHour(){
    if(status == INFECTED){
      elapsedTimeSinceInfection++;
      if(elapsedTimeSinceInfection == INFECTION_DURATION){
        srand(time(NULL));
        if(rand()%((int)(100/(FATALITY_RATE*100))) == 0){
          status = DEAD;
          return DEAD;
        } else{
          status = IMMUNE;
        }
      } else{
        return INFECTED;
      }
    } else{
      return VULNERABLE;
    }
    return -1;
  }
  void Person::setTargetLocation(Location& nlocation){
    targetLocation = &nlocation;
  }
  Location* Person::getLocation() const{
    return location;
  }
}
