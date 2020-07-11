#ifndef POPULAR_PLACE_HPP
#define POPULAR_PLACE_HPP
#include "simulation.h"
#include "place.hpp"

namespace sim{
  class PopularPlace : public Place{
  private:
    bool open;
    int numOfCasesToReopen;
    static int arraycounter;
  public:
    static PopularPlace* places[POPULAR_PLACES];
    PopularPlace();
    PopularPlace(double x, double y);
    bool isOpen() const;
    void close(int numOfCasesToReopen);
    bool reopen(int activeCases);
  };
}
#endif
