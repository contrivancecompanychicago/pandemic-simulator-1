#ifndef PERSON_HPP
#define PERSON_HPP

#include "location.hpp"
#include "place.hpp"

namespace sim{
  class Person{
  private:
    unsigned int status;
    Location* location;
    unsigned int locationStatus;
    const Place* home;
    unsigned int elapsedTimeSinceInfection;
    bool isSocialDistancing;
    unsigned int timeSinceArrival;
    Location* targetLocation;
  public:
    Person();
    ~Person();
    bool on_contact();
    Location* getLocation() const;
    int addHour();
    void action();
    void setTargetLocation(Location& nlocation);
  };
}
#endif
