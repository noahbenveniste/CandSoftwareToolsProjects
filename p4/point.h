#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifndef POINT_H
#define POINT_H

/** Minimum latitude */
#define MIN_LAT -90.0
/** Max latitude */
#define MAX_LAT 90.0
/** Min longitude */
#define MIN_LONG -180.0
/** Max longitude */
#define MAX_LONG 180.0

/** Max length of name field */
#define NAME_LEN 20
/** Max lenght of description */
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

/** A structure for storing data about a point of interest */
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

/**
 * Parses a point from standard input
 *
 * @return a pointer to the Point, or NULL if one could not be created
 */
Point *parsePoint();

/**
 * Frees malloc'd memory for a Point
 *
 * @param pt pointer to the Point to free
 */
void freePoint( Point *pt );

/**
 * Displays info about a given point to standard out
 *
 * @param pt the Point
 * @param ref the user's current coords
 */
void reportPoint( Point const *pt, Coords const *ref );

/**
 * Calculates the distance between two coords
 *
 * @param c1 the first coord
 * @param c2 the second coord
 *
 * @return the distance between c1 and c2
 */
double globalDistance( Coords const *c1, Coords const *c2);

#endif
