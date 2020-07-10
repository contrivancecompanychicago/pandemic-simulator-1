#include "popularplace.hpp"
#include "simulation.h"

namespace sim{
  PopularPlace::PopularPlace()
    :open(true){}

  PopularPlace::PopularPlace(double x, double y)
    :Place(x, y), open(true){}

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
