/** Used to check which points are within the triangle defined by
  * three sets of x,y coords input by the user, representing the
  * vertices of the triangle.
  * @file geometry.c
  * @author Noah Benveniste
  */
#include "geometry.h"

bool leftOf( double xa, double ya, double xb, double yb, double x, double y )
{
    // Calculate vectors P(a)->P(b) and P(a)->P(x,y)
    double xe = xb - xa;
    double ye = yb - ya;
    double xp = x - xa;
    double yp = y - ya;
    double result = ( xe * yp ) - ( ye * xp );
    return ( result <= 0 );
}

bool inside( double x1, double y1, double x2, double y2, double x3, double y3, double x, double y )
{
    // Calls leftOf() three times. If a point is left of all three sides of a triangle, will return true for all
    return ( leftOf( x1, y1, x2, y2, x, y ) && leftOf( x2, y2, x3, y3, x, y ) && leftOf( x3, y3, x1, y1, x, y ) );
}