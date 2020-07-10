#ifndef PLACE_HPP
#define PLACE_HPP

#include "location.hpp"

namespace sim{
  class Place{
  private:
    Location* location;
  public:
    Place();
    Place(double x, double y);
    ~Place();
  };
}
#endif
