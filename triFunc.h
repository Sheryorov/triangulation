#ifndef TRI_FUNC_H
#define TRI_FUNC_H

#include "R2Graph.h"
#include "R3Graph.h"
#include "Triangulation.h"

void plot3DFunction(
    double (*f)(const R2Point&),
    const R2Rectangle& rect,
    int numX, int numY,
    Triangulation& triangulation
);

R3Vector gradient(
    double (*f)(const R2Point&),
    const R2Point& p
);

#endif
