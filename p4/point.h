#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifndef POINT_H
#define POINT_H

#define MIN_LAT -90.0
#define MAX_LAT 90.0
#define MIN_LONG -180.0
#define MAX_LONG 180.0

#define NAME_LEN 20
#define DESC_LEN 1024

/** Multiplier for converting degrees to radians */
#define DEG_TO_RAD ( M_PI / 180.0 )

/** Radius of the earth in miles. */
#define EARTH_RADIUS 3959.0

/** Representation for a location, in latitude and longitude. */
typedef struct {
  /** Latitude value for a global location. */
  double lat;
  
  /** Longitude value for a global location. */
  double lon;
} Coords;

/** */
typedef struct {
    
    /* 
     Store the name directly in the struct; up to 20 characters
     */
    char name[21];
    
    /*
     Latitude and longitude of the Point. Latitude can be between -90 and
     90, longitude between -180 and 180.
     */
    Coords location;
    
    /*
     Pointer to the description string; not storing it here allows its length to vary.
     Can be up to 1024 characters in length (plus null terminator), cannot include any
     whitespace characters.
     */
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
