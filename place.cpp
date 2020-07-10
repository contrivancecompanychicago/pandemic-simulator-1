#include "place.hpp"

namespace sim{
  Place::Place(){
    location = new Location();
  }

  Place::Place(double x, double y){
    location = new Location(x, y);
  }
  Place::~Place(){
    delete location;
  }
}
