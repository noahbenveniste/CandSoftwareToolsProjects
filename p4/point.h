#include <stdlib.h>
#include <stdio.h>

#ifndef POINT_H
#define POINT_H

/** Representation for a location, in latitude and longitude. */
typedef struct {
  /** Latitude value for a global location. */
  double lat;
  
  /** Longitude value for a global location. */
  double lon;
} Coords;

/** */
typedef struct {
    
    /** Store the name directly in the struct; up to 20 characters */
    char name[21];
    
    /** Latitude and longitude of the Point */
    Coords location;
    
    /** Pointer to the description string; not storing it here allows its length to vary */
    char *desc;
} Point;

/*
 *
 */
Point *parsePoint();

/*
 *
 */
void freePoint( Point *pt );

/*
 *
 */
void reportPoint( Point const *pt, Coords const *ref );

/*
 *
 */
double globalDistance( Coords const *c1, Coords const *c2);

#endif
