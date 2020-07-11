#include "popularplace.hpp"
#include "simulation.h"

namespace sim{
  int PopularPlace::arraycounter = 0;
  PopularPlace* PopularPlace::places[POPULAR_PLACES];
  PopularPlace::PopularPlace()
    :open(true){
      PopularPlace::places[PopularPlace::arraycounter] = this;
      index = PopularPlace::arraycounter;
      PopularPlace::arraycounter++;
    }

  PopularPlace::PopularPlace(double x, double y)
    :Place(x, y), open(true){
      places[PopularPlace::arraycounter] = this;
      index = PopularPlace::arraycounter;
      PopularPlace::arraycounter++;
    }

  bool PopularPlace::isOpen() const{
    return open;
  }
  void PopularPlace::close(int numOfCasesToReopen){
    open = false;
  }
  bool PopularPlace::reopen(int activeCases){
    if(activeCases <= numOfCasesToReopen){
      open = true;
      return true;
    } else{
      return false;
    }
  }
}
