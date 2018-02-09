/** Functions used to check which pixels are contained within the
  * triangle when drawing.
  * @file geometry.h
  * @author Noah Benveniste
  */
#include <stdbool.h>

/** For the extra credit, the number of horizontal and vertical super-samples
    per pixel.  This is a preprocessor macro with conditional compilation
    code around it.  That lets us replace this value on the gcc line, if
    we want to.  This constant definition should probably be in triangle.c
    rather than in this header, but putting it here lets me give it to you
    with the starter. */
#ifndef SSAMP
#define SSAMP 1
#endif

/** Checks if a point x,y is left of the vector formed by the points
  * xa,ya to xb,yb
  * @param xa x comp of tail end of vector
  * @param ya y comp of tail end of vector
  * @param xb x comp of tip of vector
  * @param yb y comp of tip of vector
  * @param x x comp of point to check
  * @param y y comp of point to check
  */
bool leftOf( double xa, double ya, double xb, double yb,
             double x, double y );

/** Checks if a given point x,y is contained within a triangle defined
  * by 3 vertices.
  * @param x1 x comp of the first vertex
  * @param y1 y comp of the first vertex
  * @param x2 x comp of the second vertex
  * @param y2 y comp of the second vertex
  * @param x3 x comp of the third vertex
  * @param y3 y comp of the third vertex
  * @param x x comp of the point to check
  * @param y y comp of the point to check
  * 
  * @return true if x,y is within the triangle generated by
  *         x1,y1 , x2,y2 , x3,y3 , false otherwise
  */
bool inside( double x1, double y1, double x2, double y2,
             double x3, double y3, double x, double y );
