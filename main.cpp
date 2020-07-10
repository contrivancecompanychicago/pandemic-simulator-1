#include "location.hpp"
#include "simulation.hpp"
#include <iostream>

using namespace std; //remove this later

int main(){

  sim::Location l1(1.2, 1.2);
  cout << l1.getX() << " " <<l1.getY() << endl;
  cout << l1.atLocation(sim::Location(1, 1)) << endl;
  return 0;
}
