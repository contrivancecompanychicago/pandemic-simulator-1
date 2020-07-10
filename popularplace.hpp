#ifndef POPULAR_PLACE_HPP
#define POPULAR_PLACE_HPP
#include "place.hpp"

namespace sim{
  class PopularPlace : public Place{
  private:
    bool open;
    int numOfCasesToReopen;
  public:
    PopularPlace();
    PopularPlace(double x, double y);
    bool isOpen() const;
    void close(int numOfCasesToReopen);
    bool reopen(int activeCases);
  };
}
#endif
