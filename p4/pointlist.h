#include <stdlib.h>
#include <stdbool.h>
#include "point.h"

#ifndef POINTLIST_H
#define POINTLIST_H

/** */
typedef struct {
    
    /** The number of Point pointers in the Pointlist */
    int count;
    
    /** The current capacity of the Pointlist */
    int cap;
    
    /** Pointer to an array of pointers to Point objects */
    Point **list;
} Pointlist;

/*
 *
 */
Pointlist *createPointlist();

/*
 *
 */
void freePointlist( Pointlist *ptlist );

/*
 *
 */
bool addPoint( Pointlist *ptlist, Point *pt );

/*
 *
 */
bool removePoint( Pointlist *ptlist, char const *name );

/*
 *
 */
void listPoints( Pointlist *ptlist, Coords const *ref, bool (*test) ( Point const *pt, void *data ), void *data );

#endif