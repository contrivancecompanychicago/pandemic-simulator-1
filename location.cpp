#include <cstdlib>
#include <ctime>
#include <math.h>
#include "simulation.h"
#include "location.hpp"

#define AT 0.5

namespace sim{
  //Constructors
  Location::Location(){
    static int counter = 0;
    srand((unsigned)time(NULL)+counter);
    x = rand()%MAX_X;
    y = rand()%MAX_Y;
    counter++;
  }
  Location::Location(double xx, double yy)
    :x(xx), y(yy){}

  //Getters and setters for the coordinates
  double Location::getX() const{
    return x;
  }
  double Location::getY() const{
    return y;
  }
  void Location::setX(double nx){
    x = nx;
  }
  void Location::setY(double ny){
    y = ny;
  }

  //Get distance between this point and another
  double Location::getDistance(Location point) const{
    double nx = this->x - point.getX();
    double ny = this->y - point.getY();
    return sqrt((nx*nx)+(ny*ny));
  }
  //Check if current location is equivalent to another
  bool Location::atLocation(Location destination) const{
    return (this->getDistance(destination) <= AT);
  }
  //Move to destination
  bool Location::move(Location destination, double speed){
    double distance = this->getDistance(destination);
    double dx = destination.getX() - this->x;
    double dy = destination.getY() - this->y;
    double alpha = atan2(dy, dx);
    if(distance < speed){
      x = destination.getX();
      y = destination.getY();
      return true;
    } else{
      x += speed*cos(alpha);
      y += speed*sin(alpha);
      return false;
    }
  }
}
