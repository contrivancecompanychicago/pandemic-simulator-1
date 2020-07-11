#ifndef PERSON_HPP
#define PERSON_HPP

#include "location.hpp"
#include "place.hpp"

namespace sim{
  class Person{
  private:
    Location* location;
    Location* targetLocation;
    const Place* home;
    bool isSocialDistancing;
    unsigned int timeSinceArrival, timeTillDeparture, locationStatus, status, elapsedTimeSinceInfection;
  public:
    Person();
    ~Person();
    bool on_contact();
    Location* getLocation() const;
    int addHour();
    void action();
  };
}
#endif
