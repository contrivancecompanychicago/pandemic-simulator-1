#ifndef LOCATION_HPP
#define LOCATION_HPP

namespace sim{
  class Location{
  private:
    double x, y;
  public:
    //Constructors
    Location();
    Location(double xx, double yy);
    double getDistance(Location point) const;
    bool atLocation(Location destination) const;
    bool move(Location destination, double speed);
    //Getters and setters
    void setX(double x);
    void setY(double y);
    double getX() const;
    double getY() const;
  };
}
#endif
