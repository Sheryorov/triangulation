#ifndef SCALA_H
#define SCALA_H

#include "R2Graph.h"
#include "R3Graph.h"
#include "Triangulation.h"

void scalaMethod(
    double (*f)(const R3Point&),
    const R3Box& box,
    int numX, int numY, int numZ,
    Triangulation& triangulation
);

R3Vector gradientR3(
    double (*f)(const R3Point&),
    const R3Point& p,
    double h
);

#endif
