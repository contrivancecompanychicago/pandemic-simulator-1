#ifndef PLACE_HPP
#define PLACE_HPP

#include "location.hpp"

namespace sim{
  class Place{
  public:
    Location* location;
    Place();
    Place(double x, double y);
    ~Place();
  };
}
#endif
