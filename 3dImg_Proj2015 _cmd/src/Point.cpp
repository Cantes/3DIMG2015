#include "../include/Point.h"
#include <stdlib.h>

Point::Point()
{
    X = 0.0;
    Y = 0.0;
    Z = 0.0;
}

Point::Point(double x,double y,double z)
{
    X = x;
    Y = y;
    Z = z;
}

void Point::setPoint(Point* other)
{
    X = other->GetX();
    Y = other->GetY();
    Z = other->GetZ();
}

Point::~Point()
{
    //dtor
}

Point::Point(Point* other)
{
    X = other->GetX();
    Y = other->GetY();
    Z = other->GetZ();
   // col = new Couleur(other.Getcol());
}
