#ifndef LOCATION_HPP
#define LOCATION_HPP
namespace sim{

  class Location{
  private:
    double x, y;
  public:
    Location();
    Location(double xx, double yy);
    double getX() const;
    double getY() const;
    double getDistance(Location point) const;
    bool atLocation(Location destination) const;
    bool move(Location destination, double speed);

  };
}
#endif
