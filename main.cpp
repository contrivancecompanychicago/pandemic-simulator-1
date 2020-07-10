#include "location.hpp"
#include "simulation.hpp"
#include <iostream>

using namespace std; //remove this later
using namespace sim;

int main(){
  sim::Location l1;
  sim::Location l2;
  cout << l1.getX() << " " << l1.getY() << " " << l2.getX() << " " << l2.getY() <<endl;
  return 0;
}
